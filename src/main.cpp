#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <gtk/gtk.h>
#include <thread>
#include <atomic>

class VideoConverter {
private:
    std::string input_file;
    std::string output_file;
    std::atomic<bool> conversion_in_progress;
    GtkWidget *window;
    GtkWidget *input_entry;
    GtkWidget *output_entry;
    GtkWidget *convert_button;
    GtkWidget *progress_bar;

    static void on_convert_clicked(GtkWidget *widget, gpointer data) {
        auto *converter = static_cast<VideoConverter*>(data);
        converter->start_conversion();
    }

    static void on_window_destroy(GtkWidget *widget, gpointer data) {
        gtk_main_quit();
    }

    void start_conversion() {
        if (conversion_in_progress) {
            show_error("Conversion already in progress");
            return;
        }

        input_file = gtk_entry_get_text(GTK_ENTRY(input_entry));
        output_file = gtk_entry_get_text(GTK_ENTRY(output_entry));

        if (input_file.empty() || output_file.empty()) {
            show_error("Please enter both input and output file names");
            return;
        }

        conversion_in_progress = true;
        gtk_widget_set_sensitive(convert_button, FALSE);
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), 0.0);

        std::thread conversion_thread(&VideoConverter::convert, this);
        conversion_thread.detach();
    }

    void convert() {
        std::string command = "ffmpeg -i " + input_file + 
                              " -c:v dnxhd -profile:v dnxhr_hq -pix_fmt yuv422p -c:a alac " + 
                              output_file + " -progress pipe:1";

        FILE* pipe = popen(command.c_str(), "r");
        if (!pipe) {
            gdk_threads_add_idle(G_SOURCE_FUNC(show_error_wrapper), 
                                 const_cast<char*>("Failed to start FFmpeg process"));
            conversion_in_progress = false;
            return;
        }

        char buffer[128];
        std::string result = "";
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL) {
                result += buffer;
                if (result.find("progress=end") != std::string::npos) {
                    gdk_threads_add_idle(G_SOURCE_FUNC(update_progress_wrapper), 
                                         const_cast<gpointer>(static_cast<const void*>(this)));
                    break;
                }
            }
        }

        int status = pclose(pipe);
        conversion_in_progress = false;

        if (status == 0) {
            gdk_threads_add_idle(G_SOURCE_FUNC(show_success_wrapper), 
                                 const_cast<char*>("Video conversion completed successfully"));
        } else {
            gdk_threads_add_idle(G_SOURCE_FUNC(show_error_wrapper), 
                                 const_cast<char*>("Error occurred during video conversion"));
        }
    }

    static gboolean update_progress_wrapper(gpointer data) {
        auto *converter = static_cast<VideoConverter*>(data);
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(converter->progress_bar), 1.0);
        gtk_widget_set_sensitive(converter->convert_button, TRUE);
        return FALSE;
    }

    static gboolean show_error_wrapper(gpointer data) {
        auto *message = static_cast<char*>(data);
        VideoConverter::show_message_dialog(GTK_MESSAGE_ERROR, message);
        return FALSE;
    }

    static gboolean show_success_wrapper(gpointer data) {
        auto *message = static_cast<char*>(data);
        VideoConverter::show_message_dialog(GTK_MESSAGE_INFO, message);
        return FALSE;
    }

    static void show_message_dialog(GtkMessageType type, const char* message) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_MODAL,
                                                   type,
                                                   GTK_BUTTONS_OK,
                                                   "%s", message);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }

    void show_error(const char* message) {
        show_message_dialog(GTK_MESSAGE_ERROR, message);
    }

public:
    VideoConverter() : conversion_in_progress(false) {}

    void create_window() {
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window), "Video Converter");
        gtk_container_set_border_width(GTK_CONTAINER(window), 10);

        GtkWidget *grid = gtk_grid_new();
        gtk_container_add(GTK_CONTAINER(window), grid);

        GtkWidget *input_label = gtk_label_new("Input File:");
        gtk_grid_attach(GTK_GRID(grid), input_label, 0, 0, 1, 1);

        input_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), input_entry, 1, 0, 1, 1);

        GtkWidget *output_label = gtk_label_new("Output File:");
        gtk_grid_attach(GTK_GRID(grid), output_label, 0, 1, 1, 1);

        output_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), output_entry, 1, 1, 1, 1);

        convert_button = gtk_button_new_with_label("Convert");
        g_signal_connect(convert_button, "clicked", G_CALLBACK(on_convert_clicked), this);
        gtk_grid_attach(GTK_GRID(grid), convert_button, 0, 2, 2, 1);

        progress_bar = gtk_progress_bar_new();
        gtk_grid_attach(GTK_GRID(grid), progress_bar, 0, 3, 2, 1);

        g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);

        gtk_widget_show_all(window);
    }
};

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    VideoConverter converter;
    converter.create_window();

    gtk_main();

    return 0;
}
