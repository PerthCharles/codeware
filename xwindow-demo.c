#include <string.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    Display* display = XOpenDisplay(NULL);
    int screen = DefaultScreen(display);
    int width = DisplayWidth(display, screen)/2;
    int height = DisplayHeight(display, screen)/2;
printf("before xcreatesimplewindow\n");
sleep(3);
    Window win = XCreateSimpleWindow(display, RootWindow(display, screen),
        0, 0, width, height, 3, BlackPixel(display, screen), WhitePixel(display, screen));
XFlush(display);
printf("before xselectinput\n");
sleep(5);
    XSelectInput(display, win, ExposureMask|KeyPressMask | ButtonPressMask | StructureNotifyMask);
XFlush(display);

printf("before xcreategc\n");
sleep(5);
    GC gc = XCreateGC(display, win, 0, NULL);
XFlush(display);

printf("before xmapwindow\n");
sleep(3);
    XMapWindow(display, win);
XFlush(display);
printf("after xmapwindow\n");
sleep(5);
    while(1)
    {
//	printf("before xevent\n");
//	sleep(5);
        XEvent event = {0};
//pause();
//	printf("before next xevent\n");
//	sleep(5);
        XNextEvent(display, &event);
        switch(event.type)
        {
            case ConfigureNotify:
            {
                width = event.xconfigure.width;
                height = event.xconfigure.height;
                break;
            }
            case Expose:
            {
                XSetForeground(display, gc, WhitePixel(display, screen));
                XFillRectangle(display, win, gc, 0, 0, width, height);
               XSetForeground(display, gc, BlackPixel(display, screen));
                XDrawString(display, win, gc, width/2, height/2, "XWindow", 7);
                break;
            }
            case KeyPress:
            {
                if(event.xkey.keycode == XKeysymToKeycode(display, XK_Escape))
                {
                    XFreeGC(display, gc);
                    XCloseDisplay(display);
                    return 0;
                }
            }
            default:break;
        }
    }

    return 0;
}
