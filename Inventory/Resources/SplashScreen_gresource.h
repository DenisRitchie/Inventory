#ifndef __RESOURCE_SplashScreen_gresource_H__
#define __RESOURCE_SplashScreen_gresource_H__

#include <gio/gio.h>

extern "C"
{
    extern GResource* SplashScreen_gresource_get_resource(void);
    extern void       SplashScreen_gresource_register_resource(void);
    extern void       SplashScreen_gresource_unregister_resource(void);
}

#endif
