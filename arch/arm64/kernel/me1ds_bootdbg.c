#include <linux/io.h>
#include <linux/mm.h>
#include <linux/string.h>
#include <asm/cacheflush.h>
#include <asm/me1ds_bootdbg.h>

void me1ds_boot_stripe(int n)
{
	static void *fb;
	static bool linear;
	int b;

	if (!fb) {
		linear = pfn_valid(__phys_to_pfn(ME1DS_FB_BASE));
		if (linear)
			fb = phys_to_virt(ME1DS_FB_BASE);
		else
			fb = (void __force *)ioremap_wc(ME1DS_FB_BASE,
					ME1DS_FB_BUF_SIZE * ME1DS_FB_NR_BUF);
		if (!fb)
			return;
	}

	for (b = 0; b < ME1DS_FB_NR_BUF; b++) {
		void *p = fb + b * ME1DS_FB_BUF_SIZE + n * ME1DS_STRIPE_PITCH;

		if (linear) {
			memset(p, 0xff, ME1DS_STRIPE_SIZE);
			__flush_dcache_area(p, ME1DS_STRIPE_SIZE);
		} else {
			memset_io((void __iomem *)p, 0xff, ME1DS_STRIPE_SIZE);
		}
	}
}
