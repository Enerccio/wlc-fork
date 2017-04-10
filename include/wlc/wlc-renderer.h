#ifndef _WLC_RENDERER_H_
#define _WLC_RENDERER_H_

#include <stdint.h>
#include <stdbool.h>
#include <wlc/wlc-render.h>

struct wlc_context;
struct wlc_surface;
struct wlc_buffer;
struct wlc_view;
struct wlc_output;
struct wlc_render;
struct wlc_point;
struct wlc_geometry;
struct ctx;

struct wlc_render_api {
   const char* identifier;
   
   WLC_NONULL void (*terminate)(struct ctx *render);
   WLC_NONULL void (*resolution)(struct ctx *render, const struct wlc_size *mode, const struct wlc_size *resolution, uint32_t scale);
   WLC_NONULL void (*surface_destroy)(struct ctx *render, struct wlc_context *bound, struct wlc_surface *surface);
   WLC_NONULLV(1,2,3) bool (*surface_attach)(struct ctx *render, struct wlc_context *bound, struct wlc_surface *surface, struct wlc_buffer *buffer);
   WLC_NONULL void (*view_paint)(struct ctx *render, struct wlc_view *view);
   WLC_NONULL void (*surface_paint)(struct ctx *render, struct wlc_surface *surface, const struct wlc_geometry *geometry);
   WLC_NONULL void (*pointer_paint)(struct ctx *render, const struct wlc_point *pos);
   WLC_NONULL void (*read_pixels)(struct ctx *render, enum wlc_pixel_format format, const struct wlc_geometry *geometry, struct wlc_geometry *out_geometry, void *out_data);
   WLC_NONULL void (*write_pixels)(struct ctx *render, enum wlc_pixel_format format, const struct wlc_geometry *geometry, const void *data);
   WLC_NONULL void (*flush_fakefb)(struct ctx *render);
   WLC_NONULL void (*clear)(struct ctx *render);
};

typedef void *(*renderer_constructor) (struct wlc_render_api *api);

struct wlc_render {
   void *render; // internal renderer context (OpenGL, etc)
   struct wlc_render_api api;
};

/**
 * Sets the renderer for this output
 * 
 * this function can only be called inside the wlc_set_output_pre_backend_attach_cb callback!
 */
void wlc_output_set_renderer(wlc_handle output, renderer_constructor constructor);

/**
 * returns currently bound renderer constructor
 */
renderer_constructor wlc_output_get_renderer_constructor(wlc_handle output);

// default renderer gles2
extern void* wlc_gles2(struct wlc_render_api *api);

#endif /* _WLC_RENDERER_H_ */
