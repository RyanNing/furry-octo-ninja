#ifndef DRAWBUBBLE_H_INCLUDED
#define DRAWBUBBLE_H_INCLUDED

int get_pop_message(char *msg,char pop_message[][25]) {
    int r = 0, count = 0, pop_i = 0 ,pop_j = 0;
    int pop_num = 0;
    while (msg[r] != '\0') {
		if (msg[r] >= 0) count = count +2;
		else count = count + 1;
		pop_message[pop_i][pop_j++] = msg[r];
		if (((count % 24) == 0 )&& count !=0) {
            pop_message[pop_i][pop_j] = '\0';
            pop_i++;
            pop_j = 0;
        }
		r++;
    }
    pop_num = (count - 1) / 24 + 1;
    return pop_num;
}

GdkPixbuf *draw_bubble1(char *message)
{
    GdkPixbuf *pixbuf,*temp;
    gboolean pic_alpha;
    int bubble_size = 0;
    char pop_passage[100][25];
    memset(pop_passage,0,sizeof(pop_passage));

    bubble_size = get_pop_message(message,pop_passage);

    switch(bubble_size)
    {
        case 1:pixbuf = gdk_pixbuf_new_from_file("resource/messageBubble1_1.png", NULL);break;
        case 2:pixbuf = gdk_pixbuf_new_from_file("resource/messageBubble1_2.png", NULL);break;
        case 3:pixbuf = gdk_pixbuf_new_from_file("resource/messageBubble1_3.png", NULL);break;
        case 4:pixbuf = gdk_pixbuf_new_from_file("resource/messageBubble1_4.png", NULL);break;
        case 5:pixbuf = gdk_pixbuf_new_from_file("resource/messageBubble1_5.png", NULL);break;
        case 6:pixbuf = gdk_pixbuf_new_from_file("resource/messageBubble1_6.png", NULL);break;
        case 7:pixbuf = gdk_pixbuf_new_from_file("resource/messageBubble1_7.png", NULL);break;
        default:{
            temp = gdk_pixbuf_new_from_file("resource/messageBubble1_8.png", NULL);
            pic_alpha = gdk_pixbuf_get_has_alpha(temp);
            pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB,pic_alpha,8,200,20*bubble_size+50);
            gdk_pixbuf_scale(temp,pixbuf,0,0,200,20*bubble_size+50,0,0,1.0,(double)(20*bubble_size+50)/290.0,GDK_INTERP_BILINEAR);
            };break;
    }

    GdkPixmap *pixmap = NULL;
    gdk_pixbuf_render_pixmap_and_mask(pixbuf,&pixmap,NULL,128);

    gint w = gdk_pixbuf_get_width(pixbuf);
    gint h = gdk_pixbuf_get_height(pixbuf);

    cairo_t *cr = gdk_cairo_create(pixmap);
    for(int i=0;i<bubble_size;i++)
    {
        cairo_move_to(cr,20,35+17*i);
        cairo_set_font_size(cr,13);
        cairo_select_font_face(cr,"DongWen--Song",CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
        cairo_show_text(cr,_T(pop_passage[i]));
    }

    pixbuf = gdk_pixbuf_get_from_drawable(pixbuf,pixmap,NULL,0,0,0,0,w,h);

    g_object_unref(pixmap);

    return pixbuf;
}

GdkPixbuf *draw_bubble2(char *message)
{
    GdkPixbuf *pixbuf,*temp;
    gboolean pic_alpha;
    int bubble_size = 0;
    char pop_passage[100][25];
    memset(pop_passage,0,sizeof(pop_passage));

    bubble_size = get_pop_message(message,pop_passage);

    switch(bubble_size)
    {
        case 1:pixbuf = gdk_pixbuf_new_from_file("resource/messageBubble2_1.png", NULL);break;
        case 2:pixbuf = gdk_pixbuf_new_from_file("resource/messageBubble2_2.png", NULL);break;
        case 3:pixbuf = gdk_pixbuf_new_from_file("resource/messageBubble2_3.png", NULL);break;
        case 4:pixbuf = gdk_pixbuf_new_from_file("resource/messageBubble2_4.png", NULL);break;
        case 5:pixbuf = gdk_pixbuf_new_from_file("resource/messageBubble2_5.png", NULL);break;
        case 6:pixbuf = gdk_pixbuf_new_from_file("resource/messageBubble2_6.png", NULL);break;
        case 7:pixbuf = gdk_pixbuf_new_from_file("resource/messageBubble2_7.png", NULL);break;
        default:{
            temp = gdk_pixbuf_new_from_file("resource/messageBubble2_8.png", NULL);
            pic_alpha = gdk_pixbuf_get_has_alpha(temp);
            pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB,pic_alpha,8,200,20*bubble_size+50);
            gdk_pixbuf_scale(temp,pixbuf,0,0,200,20*bubble_size+50,0,0,1.0,(double)(20*bubble_size+50)/290.0,GDK_INTERP_BILINEAR);
            };break;
    }

    GdkPixmap *pixmap = NULL;
    gdk_pixbuf_render_pixmap_and_mask(pixbuf,&pixmap,NULL,128);

    gint w = gdk_pixbuf_get_width(pixbuf);
    gint h = gdk_pixbuf_get_height(pixbuf);

    cairo_t *cr = gdk_cairo_create(pixmap);
    for(int i=0;i<bubble_size;i++)
    {
        cairo_move_to(cr,20,35+17*i);
        cairo_set_font_size(cr,13);
        cairo_select_font_face(cr,"DongWen--Song",CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
        cairo_show_text(cr,_T(pop_passage[i]));
    }

    pixbuf = gdk_pixbuf_get_from_drawable(pixbuf,pixmap,NULL,0,0,0,0,w,h);

    g_object_unref(pixmap);

    return pixbuf;
}

#endif // DRAWBUBBLE_H_INCLUDED
