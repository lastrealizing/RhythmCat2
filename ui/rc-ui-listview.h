/*
 * RhythmCat UI List View Header Declaration
 *
 * rc-ui-listview.h
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

#ifndef HAVE_RC_UI_LISTVIEW_H
#define HAVE_RC_UI_LISTVIEW_H

#include <glib.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

/**
 * RCUiListViewPlaylistColumnFlags:
 * @RC_UI_LISTVIEW_PLAYLIST_COLUMN_ARTIST: the artist column
 * @RC_UI_LISTVIEW_PLAYLIST_COLUMN_ALBUM: the album column
 * @RC_UI_LISTVIEW_PLAYLIST_COLUMN_TRACK: the track number column
 * @RC_UI_LISTVIEW_PLAYLIST_COLUMN_YEAR: the year column
 * @RC_UI_LISTVIEW_PLAYLIST_COLUMN_FTYPE: the file type (format) column
 *
 * The enum type for control the visibility of some columns in the playlist.
 */

typedef enum {
    RC_UI_LISTVIEW_PLAYLIST_COLUMN_ARTIST = 1<<0,
    RC_UI_LISTVIEW_PLAYLIST_COLUMN_ALBUM = 1<<1,
    RC_UI_LISTVIEW_PLAYLIST_COLUMN_TRACK = 1<<2,
    RC_UI_LISTVIEW_PLAYLIST_COLUMN_YEAR = 1<<3,
    RC_UI_LISTVIEW_PLAYLIST_COLUMN_FTYPE = 1<<4
}RCUiListViewPlaylistColumnFlags;

void rc_ui_listview_init(GtkWidget **catalog_widget,
    GtkWidget **playlist_widget);
GtkWidget *rc_ui_listview_get_catalog_widget();
GtkWidget *rc_ui_listview_get_playlist_widget();
void rc_ui_listview_catalog_set_pango_attributes(const PangoAttrList *list);
void rc_ui_listview_playlist_set_pango_attributes(const PangoAttrList *list);
void rc_ui_listview_catalog_select(GtkTreeIter *iter);
void rc_ui_listview_playlist_select(GtkTreeIter *iter);
gboolean rc_ui_listview_catalog_get_cursor(GtkTreeIter *iter);
gboolean rc_ui_listview_playlist_get_cursor(GtkTreeIter *iter);
GtkTreeModel *rc_ui_listview_catalog_get_model();
GtkTreeModel *rc_ui_listview_playlist_get_model();
void rc_ui_listview_catalog_new_playlist();
void rc_ui_listview_catalog_rename_playlist();
void rc_ui_listview_catalog_delete_items();
void rc_ui_listview_playlist_select_all();
void rc_ui_listview_playlist_delete_items();
void rc_ui_listview_playlist_refresh();
void rc_ui_listview_playlist_set_column_display_mode(gboolean mode);
gboolean rc_ui_listview_playlist_get_column_display_mode();
void rc_ui_listview_playlist_set_title_format(const gchar *format);
void rc_ui_listview_playlist_set_enabled_columns(guint column_flags,
    guint enable_flags);
guint rc_ui_listview_playlist_get_enabled_columns();

G_END_DECLS

#endif

