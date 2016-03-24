#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "cw_setup.h"
#include "cw.h"
#include "filter.h"
#include "alex_setup.h"
#include "xvtr.h"
#include "band.h"
#include "ozy.h"
#include "soundcard.h"
#include "volume.h"
#include "transmit.h"

GtkWidget* cwPage;

GtkWidget* cwEnable;

GtkWidget* cwInternal;
GtkWidget* cwExternal;

GtkWidget* cwKeyermodeStraight;
GtkWidget* cwKeyermodeA;
GtkWidget* cwKeyermodeB;

GtkWidget* cwKeyerreversedYes;
GtkWidget* cwKeyerreversedNo;

GtkWidget* cwkeyerspeedFrame;
GtkWidget* cwkeyerspeedScale;

GtkWidget* cwkeyerweightFrame;
GtkWidget* cwkeyerweightScale;

GtkWidget* cwspacingON;
GtkWidget* cwspacingOFF;

void setCwkeyerspacing(int state) {
    cwkeyerspacing=state;
}

void cwInternalCallback(GtkWidget* widget,gpointer data) {
    if(GTK_TOGGLE_BUTTON(widget)->active) {
        setCwinternal(1);
    }
}

void cwExternalCallback(GtkWidget* widget,gpointer data) {
    if(GTK_TOGGLE_BUTTON(widget)->active) {
        setCwinternal(0);
    }
}

void cwKeyermodeStraightCallback(GtkWidget* widget,gpointer data) {
    if(GTK_TOGGLE_BUTTON(widget)->active) {
        setCwkeyermode(0);
    }
}

void cwKeyermodeACallback(GtkWidget* widget,gpointer data) {
    if(GTK_TOGGLE_BUTTON(widget)->active) {
        setCwinternal(1);
    }
}

void cwKeyermodeBCallback(GtkWidget* widget,gpointer data) {
    if(GTK_TOGGLE_BUTTON(widget)->active) {
        setCwinternal(2);
    }
}

void cwKeysreversedYesCallback(GtkWidget* widget,gpointer data) {
    if(GTK_TOGGLE_BUTTON(widget)->active) {
        setCwKeysreversed(1);
    }
}

void cwKeysreversedNoCallback(GtkWidget* widget,gpointer data) {
    if(GTK_TOGGLE_BUTTON(widget)->active) {
        setCwKeysreversed(0);
    }
}

void cwspacingONCallback(GtkWidget* widget,gpointer data) {
    if(GTK_TOGGLE_BUTTON(widget)->active) {
        setCwkeyerspacing(1);
    }
}

void cwspacingOFFCallback(GtkWidget* widget,gpointer data) {
    if(GTK_TOGGLE_BUTTON(widget)->active) {
        setCwkeyerspacing(0);
    }
}

void setCwkeyerspeed(int state) {
  cwkeyerspeed=state;
}

void cwkeyerspeedChanged(GtkWidget* widget, gpointer data) {
    cwkeyerspeed=gtk_range_get_value((GtkRange*)cwkeyerspeedScale);
    setCwkeyerspeed(cwkeyerspeed);
    fprintf(stderr,"setcwkeyerspeed: %d\n", cwkeyerspeed);
}

void setCwkeyerweight(int state) {
  cwkeyerweight=state;
}

void cwkeyerweightChanged(GtkWidget* widget, gpointer data) {
    cwkeyerweight=gtk_range_get_value((GtkRange*)cwkeyerweightScale);
    setCwkeyerweight(cwkeyerweight);
    fprintf(stderr,"setcwkeyerweight: %d\n", cwkeyerweight);
}

GtkWidget* cwSetupUI()
{
    init_cw();
    GtkWidget* box;
    GtkWidget* label;
    GtkWidget* item;
    char text[80];

    cwPage=gtk_vbox_new(FALSE,8);

    box=gtk_hbox_new(FALSE,2);
    label=gtk_label_new("CW setup");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,2);
    label=gtk_label_new("");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,2);
    gtk_widget_show(box);
    gtk_box_pack_start(GTK_BOX(cwPage),box,FALSE,FALSE,2);

    box=gtk_hbox_new(FALSE,2);
    label=gtk_label_new("CW:    ");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,2);

    cwInternal=gtk_radio_button_new_with_label(NULL,"Int.");
    gtk_widget_show(cwInternal);
    gtk_box_pack_start(GTK_BOX(box),cwInternal,FALSE,FALSE,2);
    g_signal_connect(G_OBJECT(cwInternal),"clicked",G_CALLBACK(cwInternalCallback),NULL);

    cwExternal=gtk_radio_button_new_with_label(gtk_radio_button_group(GTK_RADIO_BUTTON(cwInternal)),"Ext");
    gtk_widget_show(cwExternal);
    gtk_box_pack_start(GTK_BOX(box),cwExternal,FALSE,FALSE,2);
    g_signal_connect(G_OBJECT(cwExternal),"clicked",G_CALLBACK(cwExternalCallback),NULL);

    gtk_widget_show(box);
    gtk_box_pack_start(GTK_BOX(cwPage),box,FALSE,FALSE,2);

    box=gtk_hbox_new(FALSE,2);
    label=gtk_label_new("Mode");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,2);



    cwKeyermodeStraight=gtk_radio_button_new_with_label(NULL," Straight");    box=gtk_hbox_new(FALSE,2);
    label=gtk_label_new("Mode");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,2);
    gtk_widget_show(cwKeyermodeStraight);
    gtk_box_pack_start(GTK_BOX(box),cwKeyermodeStraight,FALSE,FALSE,2);
    g_signal_connect(G_OBJECT(cwKeyermodeStraight),"clicked",G_CALLBACK(cwKeyermodeStraightCallback),NULL);

    cwKeyermodeA=gtk_radio_button_new_with_label(gtk_radio_button_group(GTK_RADIO_BUTTON(cwKeyermodeStraight)),"Mode A");
    gtk_widget_show(cwKeyermodeA);
    gtk_box_pack_start(GTK_BOX(box),cwKeyermodeA,FALSE,FALSE,2);
    g_signal_connect(G_OBJECT(cwKeyermodeA),"clicked",G_CALLBACK(cwKeyermodeACallback),NULL);

    cwKeyermodeB=gtk_radio_button_new_with_label(gtk_radio_button_group(GTK_RADIO_BUTTON(cwKeyermodeA)),"Mode B");
    gtk_widget_show(cwKeyermodeB);
    gtk_box_pack_start(GTK_BOX(box),cwKeyermodeB,FALSE,FALSE,2);
    g_signal_connect(G_OBJECT(cwKeyermodeB),"clicked",G_CALLBACK(cwKeyermodeBCallback),NULL);

    gtk_widget_show(box);
    gtk_box_pack_start(GTK_BOX(cwPage),box,FALSE,FALSE,2);

    box=gtk_hbox_new(FALSE,2);
    label=gtk_label_new("CW Keyer reversed? ");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,2);

    cwKeyerreversedNo=gtk_radio_button_new_with_label(NULL,"NO");
    gtk_widget_show(cwKeyerreversedNo);
    gtk_box_pack_start(GTK_BOX(box),cwKeyerreversedNo,FALSE,FALSE,2);
    g_signal_connect(G_OBJECT(cwKeyerreversedNo),"clicked",G_CALLBACK(cwKeysreversedNoCallback),NULL);

    cwKeyerreversedYes=gtk_radio_button_new_with_label(gtk_radio_button_group(GTK_RADIO_BUTTON(cwKeyerreversedNo)),"YES");
    gtk_widget_show(cwKeyerreversedYes);
    gtk_box_pack_start(GTK_BOX(box),cwKeyerreversedYes,FALSE,FALSE,2);
    g_signal_connect(G_OBJECT(cwKeyerreversedYes),"clicked",G_CALLBACK(cwKeysreversedYesCallback),NULL);

    gtk_widget_show(box);
    gtk_box_pack_start(GTK_BOX(cwPage),box,FALSE,FALSE,2);

    box=gtk_hbox_new(FALSE,2);

    cwkeyerspeedFrame=gtk_frame_new("CW Speed");

    cwkeyerspeedScale=gtk_hscale_new_with_range(1,60,1);

    g_signal_connect(G_OBJECT(cwkeyerspeedScale),"value-changed",G_CALLBACK(cwkeyerspeedChanged),NULL);
    gtk_range_set_value((GtkRange*)cwkeyerspeedScale,cwkeyerspeed);

    gtk_widget_set_size_request(GTK_WIDGET(cwkeyerspeedScale),150,30);

    gtk_widget_show(cwkeyerspeedScale);
    gtk_container_add(GTK_CONTAINER(cwkeyerspeedFrame),cwkeyerspeedScale);
    gtk_widget_show(cwkeyerspeedFrame);
    gtk_box_pack_start(GTK_BOX(box),cwkeyerspeedFrame,FALSE,FALSE,2);
    gtk_widget_show(box);
    gtk_box_pack_start(GTK_BOX(cwPage),box,FALSE,FALSE,2);

    box=gtk_hbox_new(FALSE,2);

    cwkeyerweightFrame=gtk_frame_new("CW Weight");

    cwkeyerweightScale=gtk_hscale_new_with_range(0,100,1);

    g_signal_connect(G_OBJECT(cwkeyerweightScale),"value-changed",G_CALLBACK(cwkeyerweightChanged),NULL);
    gtk_range_set_value((GtkRange*)cwkeyerweightScale,cwkeyerweight);

    gtk_widget_set_size_request(GTK_WIDGET(cwkeyerweightScale),150,30);

    gtk_widget_show(cwkeyerweightScale);
    gtk_container_add(GTK_CONTAINER(cwkeyerweightFrame),cwkeyerweightScale);
    gtk_widget_show(cwkeyerweightFrame);
    gtk_box_pack_start(GTK_BOX(box),cwkeyerweightFrame,FALSE,FALSE,2);
    gtk_widget_show(box);
    gtk_box_pack_start(GTK_BOX(cwPage),box,FALSE,FALSE,2);

    box=gtk_hbox_new(FALSE,2);
    label=gtk_label_new("CW Spacing    ");
    gtk_widget_show(label);
    gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,2);

    cwspacingOFF=gtk_radio_button_new_with_label(NULL,"Off");
    gtk_widget_show(cwspacingOFF);
    gtk_box_pack_start(GTK_BOX(box),cwspacingOFF,FALSE,FALSE,2);
    g_signal_connect(G_OBJECT(cwspacingOFF),"clicked",G_CALLBACK(cwspacingOFFCallback),NULL);

    cwspacingON=gtk_radio_button_new_with_label(gtk_radio_button_group(GTK_RADIO_BUTTON(cwspacingOFF)),"On");
    gtk_widget_show(cwspacingON);
    gtk_box_pack_start(GTK_BOX(box),cwspacingON,FALSE,FALSE,2);
    g_signal_connect(G_OBJECT(cwspacingON),"clicked",G_CALLBACK(cwspacingONCallback),NULL);

    gtk_widget_show(box);
    gtk_box_pack_start(GTK_BOX(cwPage),box,FALSE,FALSE,2);

void   updatecwSetup();

    gtk_widget_show(cwPage);
    return cwPage;
}

void updatecwSetup(){
    switch (cwinternal) {
	case 0:
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cwExternal),TRUE);
		break;
	case 1:
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cwInternal),TRUE);
		break;
    }

    switch (cwkeyerspacing) {
	case 0:
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cwspacingOFF),TRUE);
		break;
	case 1:
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cwspacingON),TRUE);
		break;
    }

    setCwkeyerweight(cwkeyerweight);
    setCwkeyerspeed(cwkeyerspeed);
}
