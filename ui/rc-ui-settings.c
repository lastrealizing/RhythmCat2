/*
 * RhythmCat UI Settings Module
 * The setting manager for the player.
 *
 * rc-ui-settings.c
 * This file is part of RhythmCat Music Player (GTK+ Version)
 *
 * Copyright (C) 2012 - SuperCat, license: GPL v3
 *
 * RhythmCat is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * RhythmCat is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RhythmCat; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */

#include "rc-ui-settings.h"
#include "rc-common.h"
#include "rc-ui-style.h"

typedef struct RCUiSettingsPrivate
{
    GtkWidget *settings_window;
    GtkWidget *settings_notebook;
    GtkWidget *gen_autoplay_check_button;
    GtkWidget *gen_loadlast_check_button;
    GtkWidget *gen_mintray_check_button;
    GtkWidget *gen_minclose_check_button;
    GtkWidget *pl_autoenc_check_button;
    GtkWidget *pl_id3enc_entry;
    GtkWidget *pl_lrcenc_entry;
    GtkWidget *apr_theme_combo_box;
}RCUiSettingsPrivate;

static RCUiSettingsPrivate settings_priv = {0};

static void rc_ui_settings_close_button_clicked(GtkButton *button,
    gpointer data)
{
    RCUiSettingsPrivate *priv = &settings_priv;
    gtk_widget_destroy(priv->settings_window);
}

static void rc_ui_settings_window_destroy_cb(GtkWidget *widget, gpointer data)
{
    RCUiSettingsPrivate *priv = &settings_priv;
    gtk_widget_destroyed(priv->settings_window, &(priv->settings_window));
}

static void rc_ui_settings_gen_autoplay_toggled(GtkToggleButton *button,
    gpointer data)
{
    gboolean flag = gtk_toggle_button_get_active(button);
    rclib_settings_set_boolean("Player", "AutoPlayWhenStartup", flag);
}

static void rc_ui_settings_gen_loadlast_toggled(GtkToggleButton *button,
    gpointer data)
{
    gboolean flag = gtk_toggle_button_get_active(button);
    rclib_settings_set_boolean("Player", "LoadLastPosition", flag);
}

static void rc_ui_settings_gen_mintray_toggled(GtkToggleButton *button,
    gpointer data)
{
    gboolean flag = gtk_toggle_button_get_active(button);
    rclib_settings_set_boolean("MainUI", "MinimizeToTray", flag);
}

static void rc_ui_settings_gen_minclose_toggled(GtkToggleButton *button,
    gpointer data)
{
    gboolean flag = gtk_toggle_button_get_active(button);
    rclib_settings_set_boolean("MainUI", "MinimizeWhenClose", flag);
}

static inline GtkWidget *rc_ui_settings_general_build(
    RCUiSettingsPrivate *priv)
{
    GtkWidget *general_grid;
    GtkWidget *frame_label;
    GtkWidget *general_frame;
    GtkWidget *general_frame_grid;
    general_grid = gtk_grid_new();
    priv->gen_autoplay_check_button = gtk_check_button_new_with_mnemonic(
        _("_Auto play on startup"));
    priv->gen_loadlast_check_button = gtk_check_button_new_with_mnemonic(
        _("_Load the last playing position"));
    priv->gen_mintray_check_button = gtk_check_button_new_with_mnemonic(
        _("Minimize to _tray"));
    priv->gen_minclose_check_button = gtk_check_button_new_with_mnemonic(
        _("Minimize the window if the _close button is clicked"));
    general_frame = gtk_frame_new(NULL);
    frame_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(frame_label), _("<b>General</b>"));
    g_object_set(general_frame, "label-widget", frame_label, "shadow-type",
        GTK_SHADOW_NONE, "expand", TRUE, NULL);
    general_frame_grid = gtk_grid_new();
    g_object_set(priv->gen_autoplay_check_button, "active",
        rclib_settings_get_boolean("Player", "AutoPlayWhenStartup", NULL),
        NULL);
    g_object_set(priv->gen_loadlast_check_button, "active",
        rclib_settings_get_boolean("Player", "LoadLastPosition", NULL),
        NULL); 
    g_object_set(priv->gen_mintray_check_button, "active",
        rclib_settings_get_boolean("MainUI", "MinimizeToTray", NULL),
        NULL);
    g_object_set(priv->gen_minclose_check_button, "active",
        rclib_settings_get_boolean("MainUI", "MinimizeWhenClose", NULL),
        NULL);
    gtk_grid_attach(GTK_GRID(general_frame_grid),
        priv->gen_autoplay_check_button, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(general_frame_grid),
        priv->gen_loadlast_check_button, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(general_frame_grid),
        priv->gen_mintray_check_button, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(general_frame_grid),
        priv->gen_minclose_check_button, 0, 3, 1, 1);
    gtk_container_add(GTK_CONTAINER(general_frame), general_frame_grid);
    gtk_grid_attach(GTK_GRID(general_grid), general_frame, 0, 0,
        1, 1);
    g_signal_connect(priv->gen_autoplay_check_button, "toggled",
        G_CALLBACK(rc_ui_settings_gen_autoplay_toggled), NULL);
    g_signal_connect(priv->gen_loadlast_check_button, "toggled",
        G_CALLBACK(rc_ui_settings_gen_loadlast_toggled), NULL);
    g_signal_connect(priv->gen_mintray_check_button, "toggled",
        G_CALLBACK(rc_ui_settings_gen_mintray_toggled), NULL);
    g_signal_connect(priv->gen_minclose_check_button, "toggled",
        G_CALLBACK(rc_ui_settings_gen_minclose_toggled), NULL);
    return general_grid;
}

static void rc_ui_settings_pl_autoenc_toggled(GtkToggleButton *button,
    gpointer data)
{
    RCUiSettingsPrivate *priv = &settings_priv;
    gboolean flag = gtk_toggle_button_get_active(button);
    gchar *encoding, *id3_encoding;
    rclib_settings_set_boolean("Metadata", "AutoDetectEncoding", flag);
    g_object_set(priv->pl_id3enc_entry, "sensitive", !flag, NULL);
    g_object_set(priv->pl_lrcenc_entry, "sensitive", !flag, NULL);
    if(flag)
    {
        encoding = rclib_util_detect_encoding_by_locale();
        if(encoding!=NULL && strlen(encoding)>0)
        {
            id3_encoding = g_strdup_printf("%s:UTF-8", encoding);
            rclib_lyric_set_fallback_encoding(encoding);
            rclib_settings_set_string("Metadata", "LyricEncoding", encoding);
            gtk_entry_set_text(GTK_ENTRY(priv->pl_lrcenc_entry), encoding);
            rclib_tag_set_fallback_encoding(id3_encoding);
            rclib_settings_set_string("Metadata", "ID3Encoding",
                id3_encoding);
            gtk_entry_set_text(GTK_ENTRY(priv->pl_id3enc_entry),
                id3_encoding);
            g_free(id3_encoding);
        }
        g_free(encoding);
    }    
}

static void rc_ui_settings_pl_id3enc_changed(GtkEditable *editable,
    gpointer data)
{
    const gchar *text;
    text = gtk_entry_get_text(GTK_ENTRY(editable));
    rclib_settings_set_string("Metadata", "ID3Encoding", text);
}

static void rc_ui_settings_pl_lrcenc_changed(GtkEditable *editable,
    gpointer data)
{
    const gchar *text;
    text = gtk_entry_get_text(GTK_ENTRY(editable));
    rclib_settings_set_string("Metadata", "LyricEncoding", text);
}

static inline GtkWidget *rc_ui_settings_playlist_build(
    RCUiSettingsPrivate *priv)
{
    GtkWidget *playlist_grid;
    GtkWidget *frame_label;
    GtkWidget *metadata_frame;
    GtkWidget *metadata_frame_grid;
    GtkWidget *metadata_id3enc_label;
    GtkWidget *metadata_lrcenc_label;
    gchar *string;
    playlist_grid = gtk_grid_new();    
    priv->pl_autoenc_check_button = gtk_check_button_new_with_mnemonic(
        _("_Auto encoding detect (use system language settings)"));
    priv->pl_id3enc_entry = gtk_entry_new();
    priv->pl_lrcenc_entry = gtk_entry_new();
    metadata_id3enc_label = gtk_label_new(
        _("ID3 Tag fallback character encodings"));
    metadata_lrcenc_label = gtk_label_new(
        _("Lyric text fallback character encodings"));
    metadata_frame = gtk_frame_new(NULL);
    frame_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(frame_label), _("<b>Metadata</b>"));
    g_object_set(metadata_frame, "label-widget", frame_label, "shadow-type",
        GTK_SHADOW_NONE, "expand", TRUE, NULL);
    metadata_frame_grid = gtk_grid_new();
    g_object_set(priv->pl_id3enc_entry, "margin-left", 2, "margin-right",
        2, "margin-top", 2, "margin-bottom", 2, "hexpand-set", TRUE,
        "hexpand", TRUE, NULL);
    g_object_set(priv->pl_lrcenc_entry, "margin-left", 2, "margin-right",
        2, "margin-top", 2, "margin-bottom", 2, "hexpand-set", TRUE,
        "hexpand", TRUE, NULL);
    if(rclib_settings_get_boolean("Metadata", "AutoDetectEncoding", NULL))
    {
        g_object_set(priv->pl_autoenc_check_button, "active", TRUE, NULL);
        g_object_set(priv->pl_id3enc_entry, "sensitive", FALSE, NULL);
        g_object_set(priv->pl_lrcenc_entry, "sensitive", FALSE, NULL);
    }
    string = rclib_settings_get_string("Metadata", "ID3Encoding", NULL);
    if(string!=NULL)
        gtk_entry_set_text(GTK_ENTRY(priv->pl_id3enc_entry), string);
    g_free(string);
    string = rclib_settings_get_string("Metadata", "LyricEncoding", NULL);
    if(string!=NULL)
        gtk_entry_set_text(GTK_ENTRY(priv->pl_lrcenc_entry), string);
    g_free(string);
    gtk_grid_attach(GTK_GRID(metadata_frame_grid),
        priv->pl_autoenc_check_button, 0, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(metadata_frame_grid),
        metadata_id3enc_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(metadata_frame_grid),
        priv->pl_id3enc_entry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(metadata_frame_grid),
        metadata_lrcenc_label, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(metadata_frame_grid),
        priv->pl_lrcenc_entry, 1, 2, 1, 1);
    gtk_container_add(GTK_CONTAINER(metadata_frame), metadata_frame_grid);
    gtk_grid_attach(GTK_GRID(playlist_grid), metadata_frame, 0, 0,
        1, 1);
    g_signal_connect(priv->pl_autoenc_check_button, "toggled",
        G_CALLBACK(rc_ui_settings_pl_autoenc_toggled), NULL);        
    g_signal_connect(priv->pl_id3enc_entry, "changed",
        G_CALLBACK(rc_ui_settings_pl_id3enc_changed), NULL);
    g_signal_connect(priv->pl_lrcenc_entry, "changed",
        G_CALLBACK(rc_ui_settings_pl_lrcenc_changed), NULL);
    return playlist_grid;
}

static void rc_ui_settings_apr_theme_changed(GtkComboBox *widget,
    gpointer data)
{
    GtkTreeModel *model;
    GtkTreeIter iter;
    gchar *theme;
    gchar *theme_settings;
    gchar *theme_file;
    gboolean embeded_flag;
    gboolean theme_flag = FALSE;
    const RCUiStyleEmbededTheme *theme_embeded;
    guint theme_number;
    gint i;
    model = gtk_combo_box_get_model(widget);
    if(model==NULL) return;
    if(!gtk_combo_box_get_active_iter(widget, &iter)) return;
    gtk_tree_model_get(model, &iter, 1, &embeded_flag, 2, &theme, -1);
    if(embeded_flag)
    {
        theme_settings = g_strdup_printf("embeded-theme:%s", theme);
        theme_embeded = rc_ui_style_get_embeded_theme(&theme_number);
        for(i=0;i<theme_number;i++)
        {
            if(g_strcmp0(theme, theme_embeded[i].name)==0)
            {
                theme_flag = rc_ui_style_css_set_data(theme_embeded[i].data,
                    theme_embeded[i].length);
            }
        }
        if(theme_flag)
            rclib_settings_set_string("MainUI", "Theme", theme_settings);
        g_free(theme_settings);
    }
    else
    {
        theme_file = g_build_filename(theme, "gtk3.css", NULL);
        theme_flag = rc_ui_style_css_set_file(theme_file);
        g_free(theme_file);
        if(theme_flag)
            rclib_settings_set_string("MainUI", "Theme", theme);
    }
    g_free(theme);
    
}

static inline GtkWidget *rc_ui_settings_appearance_build(
    RCUiSettingsPrivate *priv)
{
    GtkWidget *appearance_grid;
    GtkWidget *frame_label;
    GtkWidget *theme_frame;
    GtkWidget *theme_frame_grid;
    GtkListStore *store;
    GtkCellRenderer *renderer;
    GtkTreeIter iter;
    GSList *theme_list, *foreach;
    const RCUiStyleEmbededTheme *theme_embeded;
    guint theme_number;
    gint i;
    const gchar *path;
    gchar *theme_name;
    gchar *theme_settings;
    gboolean theme_embeded_flag = FALSE;
    appearance_grid = gtk_grid_new();
    theme_frame = gtk_frame_new(NULL);
    frame_label = gtk_label_new(NULL);
    store = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_BOOLEAN, G_TYPE_STRING);
        renderer = gtk_cell_renderer_text_new();
    priv->apr_theme_combo_box = gtk_combo_box_new_with_model(GTK_TREE_MODEL(store));
    g_object_unref(store);
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(priv->apr_theme_combo_box),
        renderer, TRUE);
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(priv->apr_theme_combo_box),
        renderer, "text", 0, NULL);
    gtk_label_set_markup(GTK_LABEL(frame_label), _("<b>Theme</b>"));
    g_object_set(theme_frame, "label-widget", frame_label, "shadow-type",
        GTK_SHADOW_NONE, "expand", TRUE, NULL);
    theme_frame_grid = gtk_grid_new();
    g_object_set(priv->apr_theme_combo_box, "margin-left", 2, "margin-right",
        2, "margin-top", 2, "margin-bottom", 2, "hexpand-set", TRUE,
        "hexpand", TRUE, NULL);
    theme_settings = rclib_settings_get_string("MainUI", "Theme", NULL);
    if(theme_settings!=NULL)
    {
        theme_embeded_flag = g_str_has_prefix(theme_settings,
            "embeded-theme:");
    }
    theme_embeded = rc_ui_style_get_embeded_theme(&theme_number);
    for(i=0;i<theme_number;i++)
    {
        theme_name = g_strdup_printf(_("%s (Embeded)"),
            theme_embeded[i].name);
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, theme_name, 1, TRUE, 2,
            theme_embeded[i].name, -1);
        g_free(theme_name);
        if(theme_embeded_flag)
        {
            if(g_strcmp0(theme_settings+14, theme_embeded[i].name)==0)
            {
                gtk_combo_box_set_active_iter(GTK_COMBO_BOX(
                    priv->apr_theme_combo_box), &iter);
            }
        }
    }
    theme_list = rc_ui_style_search_theme_paths();
    for(foreach=theme_list;foreach!=NULL;foreach=g_slist_next(foreach))
    {
        path = foreach->data;
        if(path==NULL) continue;
        theme_name = g_path_get_basename(path);
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, theme_name, 1, FALSE, 2, path,
            -1);
        g_free(theme_name);
        if(g_strcmp0(theme_settings, path)==0)
        {
            gtk_combo_box_set_active_iter(GTK_COMBO_BOX(
                priv->apr_theme_combo_box), &iter);
        }
    }
    if(theme_list!=NULL)
        g_slist_free_full(theme_list, g_free);
    g_free(theme_settings);
    if(gtk_combo_box_get_active(GTK_COMBO_BOX(priv->apr_theme_combo_box))<0)
        gtk_combo_box_set_active(GTK_COMBO_BOX(priv->apr_theme_combo_box), 0);
    gtk_grid_attach(GTK_GRID(theme_frame_grid),
        priv->apr_theme_combo_box, 0, 0, 1, 1);
    gtk_container_add(GTK_CONTAINER(theme_frame), theme_frame_grid);
    gtk_grid_attach(GTK_GRID(appearance_grid), theme_frame, 0, 0,
        1, 1);
    g_signal_connect(priv->apr_theme_combo_box, "changed",
        G_CALLBACK(rc_ui_settings_apr_theme_changed), NULL);
    return appearance_grid;
}

static inline void rc_ui_settings_window_init()
{
    RCUiSettingsPrivate *priv = &settings_priv;
    GtkWidget *close_button;
    GtkWidget *main_grid;
    GtkWidget *general_label;
    GtkWidget *playlist_label;
    GtkWidget *appearance_label;
    GtkWidget *button_hbox;
    priv->settings_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    main_grid = gtk_grid_new();
    priv->settings_notebook = gtk_notebook_new();
    close_button = gtk_button_new_from_stock(GTK_STOCK_CLOSE);
    general_label = gtk_label_new(_("General"));
    playlist_label = gtk_label_new(_("Playlist"));
    appearance_label = gtk_label_new(_("Appearance"));
    button_hbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    g_object_set(priv->settings_window, "title", _("Player Preferences"),
        "window-position", GTK_WIN_POS_CENTER, "has-resize-grip", FALSE,
        "default-width", 350, "default-height", 300, "icon-name",
        GTK_STOCK_PREFERENCES, "type-hint", GDK_WINDOW_TYPE_HINT_DIALOG,
        NULL);
    g_object_set(priv->settings_notebook, "margin-left", 2, "margin-right",
        2, "margin-top", 4, "margin-bottom", 4, "tab-pos", GTK_POS_LEFT,
        "expand", TRUE, NULL);
    g_object_set(button_hbox, "layout-style", GTK_BUTTONBOX_END,
        "hexpand-set", TRUE, "hexpand", TRUE, "spacing", 4,
        "margin-left", 4, "margin-right", 4, "margin-top", 4,
        "margin-bottom", 4, NULL);
    gtk_notebook_append_page(GTK_NOTEBOOK(priv->settings_notebook),
        rc_ui_settings_general_build(priv), general_label);
    gtk_notebook_append_page(GTK_NOTEBOOK(priv->settings_notebook),
        rc_ui_settings_playlist_build(priv), playlist_label);
    gtk_notebook_append_page(GTK_NOTEBOOK(priv->settings_notebook),
        rc_ui_settings_appearance_build(priv), appearance_label);
    gtk_box_pack_start(GTK_BOX(button_hbox), close_button, FALSE, FALSE, 2);
    gtk_grid_attach(GTK_GRID(main_grid), priv->settings_notebook, 0, 0,
        1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), button_hbox, 0, 1, 1, 1);
    gtk_container_add(GTK_CONTAINER(priv->settings_window), main_grid);
    g_signal_connect(close_button, "clicked",
        G_CALLBACK(rc_ui_settings_close_button_clicked), NULL); 
    g_signal_connect(G_OBJECT(priv->settings_window), "destroy",
        G_CALLBACK(rc_ui_settings_window_destroy_cb), NULL);
    gtk_widget_show_all(priv->settings_window);
}

/**
 * rc_ui_plugin_window_show:
 *
 * Show a player configuration window.
 */

void rc_ui_settings_window_show()
{
    RCUiSettingsPrivate *priv = &settings_priv;
    if(priv->settings_window==NULL)
        rc_ui_settings_window_init();
    else
        gtk_window_present(GTK_WINDOW(priv->settings_window));
}

/**
 * rc_ui_settings_window_destroy:
 *
 * Destroy the player configuration window.
 */

void rc_ui_settings_window_destroy()
{
    RCUiSettingsPrivate *priv = &settings_priv;
    if(priv->settings_window!=NULL)
        gtk_widget_destroy(priv->settings_window);
}


