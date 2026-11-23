#ifndef __ASM_ME1DS_BOOTDBG_H
#define __ASM_ME1DS_BOOTDBG_H

/* LG K130 framebuffer as left by lk: 480x854 (864 aligned), 32 bpp, 3 buffers */
#define ME1DS_FB_BASE		0x7F870000
#define ME1DS_FB_STRIDE		1920
#define ME1DS_FB_BUF_SIZE	(ME1DS_FB_STRIDE * 864)
#define ME1DS_FB_NR_BUF		3
#define ME1DS_STRIPE_PITCH	(105 * ME1DS_FB_STRIDE)
#define ME1DS_STRIPE_SIZE	(85 * ME1DS_FB_STRIDE)

#ifndef __ASSEMBLY__
#ifdef CONFIG_ME1DS_BOOT_STRIPES
void me1ds_boot_stripe(int n);
#else
static inline void me1ds_boot_stripe(int n) { }
#endif
#endif

#endif
