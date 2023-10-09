/*
 * Copyright 2023 Colin S. Gordon <colin.s.gordon@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/bus.h>
#include <sys/module.h>
#include <sys/queue.h>
#include <sys/taskqueue.h>

#include <machine/bus.h>

#include <dev/mmc/bridge.h>
#include <dev/mmc/mmc_fdt_helpers.h>

#include <dev/ofw/ofw_bus_subr.h>

#include <dev/extres/clk/clk.h>

#include <dev/mmc/host/dwmmc_var.h>

#include "opt_mmccam.h"

static struct ofw_compat_data compat_data[] = {
	{"starfive,jh7110-mmc",	1},
	{NULL,			0},
};

static int dwmmc_starfive_update_ios(struct dwmmc_softc *sc, struct mmc_ios *ios);

static int
starfive_dwmmc_probe(device_t dev)
{

	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	if (ofw_bus_search_compatible(dev, compat_data)->ocd_data == 0)
		return (ENXIO);
	device_printf(dev, "Found JH7110 mmc controller!\n");

	device_set_desc(dev, "JH7110 MMC Controller (StarFive)");

	return (BUS_PROBE_VENDOR);
}

static int
starfive_dwmmc_attach(device_t dev)
{
	struct dwmmc_softc *sc;

	sc = device_get_softc(dev);
	sc->hwtype = HWTYPE_STARFIVE;
	sc->update_ios = &dwmmc_starfive_update_ios;

	/*
	 * TODO: For now, since we don't seem to require any special logic (OpenBSD doesn't either) for this, we could try just stopping in the debugger
	 * when altera_dwmmc_probe is called, and overriding its return to attach; it's the most generic of the bunch...
	 *
	 * Eventually I'll have to adapt the freebsd-vf2.sh script to package the output of my installkernel and installworld
	 */

	return (dwmmc_attach(dev));
}

static int
dwmmc_starfive_update_ios(struct dwmmc_softc *sc, struct mmc_ios *ios)
{
	// 
	return (0);
}

static device_method_t starfive_dwmmc_methods[] = {
	/* bus interface */
	DEVMETHOD(device_probe, starfive_dwmmc_probe),
	DEVMETHOD(device_attach, starfive_dwmmc_attach),
	DEVMETHOD(device_detach, dwmmc_detach),

	DEVMETHOD_END
};

DEFINE_CLASS_1(starfive_dwmmc, starfive_dwmmc_driver, starfive_dwmmc_methods,
    sizeof(struct dwmmc_softc), dwmmc_driver);

DRIVER_MODULE(starfive_dwmmc, simplebus, starfive_dwmmc_driver, 0, 0);
DRIVER_MODULE(starfive_dwmmc, ofwbus, starfive_dwmmc_driver, NULL, NULL);
#ifndef MMCCAM
MMC_DECLARE_BRIDGE(starfive_dwmmc);
#endif
