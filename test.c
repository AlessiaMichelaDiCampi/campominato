#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
GtkWidget *g_lbl_label;
GtkWidget *window_gioco;
GtkWidget *g_lbl_label_info;
GtkWidget *bottone_torna_al_menu;
GtkWidget *g_button_info;
GtkWidget *g_griglia;
GtkWidget *g_entry_r_c;
GtkWidget *g_entry_bombe;
GtkWidget *lbl_bandiera;
GtkWidget *come_back;
GtkWidget *lbl_gioco;
GtkWidget *carica;
GtkWidget *genera;
GtkWidget *button;
GtkWidget *grid;
GtkWidget *numero;
GtkLabel *totale;
GtkWidget *griglia_gioco;
GtkWidget *button_ok;
GtkWidget *quit;
GtkWidget *info;
const gchar *bombe;
const gchar *tot;
const gchar *righe_colonne;


int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;
	
	/*init gtk lib*/
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "test2.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "test2"));
    window_gioco = GTK_WIDGET(gtk_builder_get_object(builder, "containergioco"));
    genera = GTK_WIDGET(gtk_builder_get_object(builder, "genera"));
    g_lbl_label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
    g_lbl_label_info = GTK_WIDGET(gtk_builder_get_object(builder, "label_info"));
    g_button_info = GTK_WIDGET(gtk_builder_get_object(builder, "info"));
    g_griglia = GTK_WIDGET(gtk_builder_get_object(builder, "griglia"));
    g_entry_r_c = GTK_WIDGET(gtk_builder_get_object(builder, "entry_r_c"));
    g_entry_bombe = GTK_WIDGET(gtk_builder_get_object(builder, "entry_bombe"));
    come_back = GTK_WIDGET(gtk_builder_get_object(builder, "come_back"));
    button = GTK_WIDGET(gtk_builder_get_object(builder, "button"));
    lbl_gioco = GTK_WIDGET(gtk_builder_get_object(builder, "button"));
    lbl_bandiera = GTK_WIDGET(gtk_builder_get_object(builder, "button"));
    numero = GTK_WIDGET(gtk_builder_get_object(builder, "numero"));
    carica = GTK_WIDGET(gtk_builder_get_object(builder, "carica"));
    grid = GTK_WIDGET(gtk_builder_get_object(builder, "grid"));
    totale = GTK_LABEL(gtk_builder_get_object(builder, "totale"));
    griglia_gioco = GTK_WIDGET(gtk_builder_get_object(builder, "griglia_gioco"));
    bottone_torna_al_menu = GTK_WIDGET(gtk_builder_get_object(builder, "torna_al_menu"));
    button_ok = GTK_WIDGET(gtk_builder_get_object(builder, "ok"));
    quit = GTK_WIDGET(gtk_builder_get_object(builder, "quit"));
    info = GTK_WIDGET(gtk_builder_get_object(builder, "info"));
	
    
    gtk_builder_connect_signals(builder, NULL);
 
    g_object_unref(builder);
	/*show window*/
    gtk_widget_show(window);
                    
    gtk_main();
 
    return 0;
}
 
// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}
void on_info_clicked(){
	

	/*gtk_label_set_text(GTK_LABEL(g_lbl_label), "IL gioco è stato creato da me e altri due");
	*/gtk_widget_hide(g_griglia);
	gtk_widget_hide(g_lbl_label);
	gtk_widget_show(g_lbl_label_info);
 }
 void on_genera_clicked(){
	
	gtk_widget_show(g_griglia);
	gtk_widget_show(g_entry_r_c);
	gtk_widget_show(g_entry_bombe);
	gtk_widget_show(button_ok);
	gtk_widget_hide(g_lbl_label);
	gtk_widget_hide(carica);
	gtk_widget_hide(genera);
	gtk_widget_hide(g_button_info);
	gtk_widget_hide(g_lbl_label_info);

	
 }


gboolean right_click(GtkWidget *btn, GdkEventButton *event, gpointer userdata)
{
	if (event->type == GDK_BUTTON_PRESS && event->button == 3) {
		return true;
	}
	if (event->type == GDK_BUTTON_PRESS && event->button == 1){
		return true;
	}
	return true;
}


gboolean btn_press_callback(GtkWidget *button, GdkEventButton *event, gpointer userdata){
	if (  (event->type == GDK_BUTTON_PRESS && event->button == 3) && (strcmp((gtk_button_get_label(GTK_BUTTON(button))),"stato iniziale")==0)   ){
		   gtk_button_set_label(GTK_BUTTON(button), "bandiera");
		
	}
	 else if ((event->type == GDK_BUTTON_PRESS && event->button == 1) && (strcmp((gtk_button_get_label(GTK_BUTTON(button))),"bandiera")==0)){
		 gtk_button_set_label(GTK_BUTTON(button), "stato iniziale");
		 
	}else if((event->type == GDK_BUTTON_PRESS && event->button == 1) && !(strcmp((gtk_button_get_label(GTK_BUTTON(button))),"bandiera")==0))
	      gtk_button_set_label(GTK_BUTTON(button), "numero");
	else if ((event->type == GDK_BUTTON_PRESS && event->button == 3) && (strcmp((gtk_button_get_label(GTK_BUTTON(button))),"numero")==0))
		 gtk_button_set_label(GTK_BUTTON(button), "numero");
	
	return true;
}


 int on_ok_clicked(){
	 int conta;
	 int i;
	 int j;
	 int r;
	 int b;
	 int turn;
	 gtk_widget_show(come_back);
	 gtk_widget_hide(g_griglia);
	 gtk_widget_show(bottone_torna_al_menu);
	 gtk_widget_show(griglia_gioco);
	 turn=0;
	 bombe=gtk_entry_get_text(GTK_ENTRY(g_entry_bombe));
	 righe_colonne=gtk_entry_get_text(GTK_ENTRY(g_entry_r_c));
	 r=atoi(righe_colonne);
	 b=atoi(bombe);
	 if(b<(r * r)){
		
	 tot=strcat((char*)bombe,(char*)righe_colonne);
	/* gtk_widget_show(totale);*/
	/* Here we construct the container that is going pack our buttons */
	grid = gtk_grid_new ();

	/* Pack the container in the window */
	 griglia_gioco = gtk_grid_new ();
	 
	 gtk_container_add (GTK_CONTAINER (window_gioco), griglia_gioco);
	 gtk_label_set_text(totale,tot);
	 
	 conta=atoi(righe_colonne);
	 for(i=0;i<conta;i++){
		 for(j=0;j<conta;j++){
		 button = gtk_button_new_with_label ("stato iniziale"); /* creazione bottoni ,devo mettere la griglia dei bottoni al centro*/
		 gtk_grid_attach (GTK_GRID (griglia_gioco), button, i, j, 1, 1);
		
		
		 if( g_signal_connect( G_OBJECT(button),"button-press-event",G_CALLBACK(btn_press_callback),NULL))
		  turn++;
		 
		}
     }
     	
	 gtk_widget_show_all (griglia_gioco);
	 gtk_label_set_text(totale,turn);
	 return turn;
	 	 
	 }else{
	  gtk_container_add (GTK_CONTAINER (window_gioco), (gtk_label_new ("TROPPE BOMBE")));
	  return 0;
	 }
	/*altrimenti dire che non va bene che le bombe siano di più delle righe*colonne*/
}

void on_torna_al_menu_clicked(){
	 gtk_widget_hide(griglia_gioco);
	 gtk_widget_hide(come_back);
	 gtk_widget_hide(bottone_torna_al_menu);
	 gtk_widget_hide(g_entry_bombe);
	 gtk_widget_hide(g_entry_r_c);
	 gtk_widget_hide(button_ok);
	 gtk_widget_hide(quit);
	 gtk_widget_show(genera);
	 gtk_widget_show(info);
	 gtk_widget_show(g_lbl_label);
	 gtk_widget_show(quit);
	 gtk_widget_show(carica);
	 

}
	  
	  
	  
	  
