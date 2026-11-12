#ifndef BLUEBOX_FX1_ALLOC_REPORT_H
#define BLUEBOX_FX1_ALLOC_REPORT_H
#include <stdint.h>
/* M7 publishes one cache-line-aligned allocator snapshot for the M4 Tools UI.
 * This is diagnostic only: it does not reserve, allocate, or free SDRAM. */
#define FX1_ALLOC_REPORT_ADDR 0x38800e80u
#define FX1_ALLOC_REPORT_MAGIC 0x46584152u
struct fx1_alloc_report {
    uint32_t magic;
    uint32_t cursor_before_fx1;
    uint32_t limit;
    uint32_t fx1_requested;
    uint32_t cursor_after_fx1;
    uint32_t fx2_requested;
    uint32_t cursor_after_fx2;
    uint32_t remaining;
};
#define FX1_ALLOC_REPORT ((volatile struct fx1_alloc_report *)FX1_ALLOC_REPORT_ADDR)
_Static_assert(sizeof(struct fx1_alloc_report)==32,"allocator report occupies one cache line");
#endif
