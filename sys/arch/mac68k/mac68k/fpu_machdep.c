/*	$NetBSD: fpu_machdep.c,v 1.1 2011/11/15 12:23:22 tsutsui Exp $	*/

/*-
 * Copyright (c) 1996 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Gordon W. Ross.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD: fpu_machdep.c,v 1.1 2011/11/15 12:23:22 tsutsui Exp $");

#include "opt_fpu_emulate.h"

/*
 * Floating Point Unit (MC68881/882/040) initialization.
 */

#include <sys/param.h>

#include <machine/cpu.h>
#include <machine/frame.h>

/*
 * FPU type; emulator uses FPU_NONE
 */

extern label_t *nofault;

static const char *fpu_descr[] = {
#ifdef	FPU_EMULATE
	[FPU_NONE] = "emulator",
#else
	[FPU_NONE] = "no math support",
#endif
	[FPU_68881] = "mc68881",
	[FPU_68882] = "mc68882",
	[FPU_68040] = "mc68040",
	[FPU_68060] = "mc68060",
	[FPU_UNKNOWN] = "unknown"
};

void
initfpu(void)
{
	const char *descr;

	fputype = fpu_probe();

	/* Generate a reference FPU idle frame. */
	if (fputype != FPU_NONE)
		m68k_make_fpu_idle_frame();

	if ((0 <= fputype) && (fputype <= 3))
		descr = fpu_descr[fputype];
	else
		descr = "unknown type";

	printf("fpu: %s\n", descr);
}
