#include <gtk/gtk.h>

/*Variáveis de Acesso ao Arquivo*/
GtkBuilder *builder;
/*Variáveis de Acesso à Janela*/
GtkWidget *window;

int main(int argc, char *argv[]) {

	gtk_init(&argc, &argv);
 
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "InterfaceCarrossel.glade", NULL);
 
	window = GTK_WIDGET(gtk_builder_get_object(builder, "janela"));
	gtk_builder_connect_signals(builder, NULL);

	g_object_unref(builder);
 
	gtk_widget_show(window);
	gtk_main();

	return 0;
}