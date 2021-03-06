/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author:Mark Yao <mark.yao@rock-chips.com>
 *
 * based on exynos_drm_drv.h
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _ROCKCHIP_DRM_DRV_H
#define _ROCKCHIP_DRM_DRV_H

#include <drm/drm_atomic.h>
#include <drm/drm_fb_helper.h>

#include <linux/module.h>
#include <linux/component.h>

#define ROCKCHIP_MAX_FB_BUFFER	3
#define ROCKCHIP_MAX_CONNECTOR	2
#define ROCKCHIP_MAX_CRTC	2

struct drm_device;
struct drm_connector;

/*
 * Rockchip drm_file private structure.
 *
 * @gem_cpu_acquire_list: list of GEM objects we hold acquires on
 */
struct rockchip_drm_file_private {
	struct list_head		gem_cpu_acquire_list;
};

/*
 * Rockchip drm private structure.
 *
 * @crtc: array of enabled CRTCs, used to map from "pipe" to drm_crtc.
 * @num_pipe: number of pipes for this device.
 * @cpu_fence_context: fence context used for CPU acquire/release
 * @cpu_fence_seqno: fence sequence number
 */
struct rockchip_drm_private {
	struct drm_fb_helper fbdev_helper;
	struct drm_gem_object *fbdev_bo;
#ifdef CONFIG_DRM_DMA_SYNC
	unsigned int cpu_fence_context;
	atomic_t cpu_fence_seqno;
#endif
};

int rockchip_drm_encoder_get_mux_id(struct device_node *node,
				    struct drm_encoder *encoder);
int rockchip_drm_crtc_mode_config(struct drm_crtc *crtc, int connector_type,
				  int out_mode);
int rockchip_drm_crtc_enable_vblank(struct drm_device *dev, int pipe);
void rockchip_drm_crtc_disable_vblank(struct drm_device *dev, int pipe);
int rockchip_drm_dma_attach_device(struct drm_device *drm_dev,
				   struct device *dev);
void rockchip_drm_dma_detach_device(struct drm_device *drm_dev,
				    struct device *dev);

#endif /* _ROCKCHIP_DRM_DRV_H_ */
