#ifndef _WLC_CONTEXT_H_
#define _WLC_CONTEXT_H_

#include <stdbool.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

struct wl_display;
struct wlc_backend_surface;
struct ctx;

struct wlc_context_api {
   WLC_NONULL void (*terminate)(struct ctx *context);
   WLC_NONULL bool (*bind)(struct ctx *context);
   WLC_NONULL bool (*bind_to_wl_display)(struct ctx *context, struct wl_display *display);
   WLC_NONULL void (*swap)(struct ctx *context, struct wlc_backend_surface *bsurface);
   WLC_NONULL void* (*get_proc_address)(struct ctx *context, const char *procname);

   // EGL
   WLC_NONULL EGLBoolean (*query_buffer)(struct ctx *context, struct wl_resource *buffer, EGLint attribute, EGLint *value);
   WLC_NONULL EGLImageKHR (*create_image)(struct ctx *context, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list);
   WLC_NONULL EGLBoolean (*destroy_image)(struct ctx *context, EGLImageKHR image);
};

struct wlc_context {
   void *context; // internal surface context (EGL, etc)
   struct wlc_context_api api;
};

WLC_NONULL void* wlc_context_get_proc_address(struct wlc_context *context, const char *procname);
WLC_NONULL EGLBoolean wlc_context_query_buffer(struct wlc_context *context, struct wl_resource *buffer, EGLint attribute, EGLint *value);
WLC_NONULL EGLImageKHR wlc_context_create_image(struct wlc_context *context, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list);
WLC_NONULL EGLBoolean wlc_context_destroy_image(struct wlc_context *context, EGLImageKHR image);
WLC_NONULL bool wlc_context_bind(struct wlc_context *context);
WLC_NONULL bool wlc_context_bind_to_wl_display(struct wlc_context *context, struct wl_display *display);
WLC_NONULL void wlc_context_swap(struct wlc_context *context, struct wlc_backend_surface *bsurface);
void wlc_context_release(struct wlc_context *context);
WLC_NONULL bool wlc_context(struct wlc_context *context, struct wlc_backend_surface *bsurface);

#endif /* _WLC_CONTEXT_H_ */
