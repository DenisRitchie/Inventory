#pragma once

#ifdef UNICODE
#undef UNICODE
#endif

#ifdef _UNICODE
#undef _UNICODE
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4250)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)
#endif

#include <gtkmm.h>
#include <gtk/gtk.h>
#include <gdk/win32/gdkwin32.h>
