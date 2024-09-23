/**
 * @file main.cpp
 *
 */
/* Copyright (C) 2022-2024 by Arjan van Vught mailto:info@gd32-dmx.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <cstdint>
#include <cstdio>
#include <cassert>

#include "hardware.h"
#include "network.h"
#include "networkconst.h"

#include "net/apps/mdns.h"

#if defined (ENABLE_NTP_CLIENT)
# include "net/apps/ntpclient.h"
#endif

#include "displayudf.h"
#include "displayudfparams.h"
#include "displayhandler.h"

#include "pp.h"

#include "pixeldmxconfiguration.h"
#include "pixeltype.h"
#include "pixeltestpattern.h"
#include "pixeldmxparams.h"

#include "ws28xxmulti.h"
#include "ws28xxdmxmulti.h"

#if defined (NODE_RDMNET_LLRP_ONLY)
# include "rdmdeviceparams.h"
# include "rdmnetdevice.h"
# include "rdmnetconst.h"
# include "rdmpersonality.h"
# include "rdm_e120.h"
#endif

#include "remoteconfig.h"
#include "remoteconfigparams.h"

#include "configstore.h"


#include "firmwareversion.h"
#include "software_version.h"

void Hardware::RebootHandler() {
	WS28xxMulti::Get()->Blackout();
	PixelPusher::Get()->Stop();
}

int main() {
	Hardware hw;
	DisplayUdf display;
	ConfigStore configStore;
	display.TextStatus(NetworkConst::MSG_NETWORK_INIT, CONSOLE_YELLOW);
	Network nw;
	MDNS mDns;
	display.TextStatus(NetworkConst::MSG_NETWORK_STARTED, CONSOLE_GREEN);
	FirmwareVersion fw(SOFTWARE_VERSION, __DATE__, __TIME__);

	fw.Print("PixelPusher controller {8x 4 Universes}");
	

#if defined (ENABLE_NTP_CLIENT)
	NtpClient ntpClient;
	ntpClient.Start();
	ntpClient.Print();
#endif

	mDns.ServiceRecordAdd(nullptr, mdns::Services::PP);

	PixelDmxConfiguration pixelDmxConfiguration;

	PixelDmxParams pixelDmxParams;
	pixelDmxParams.Load();
	pixelDmxParams.Set();

	WS28xxDmxMulti pixelDmxMulti;

	PixelPusher pp;

	const auto nActivePorts = pixelDmxConfiguration.GetOutputPorts();

	pp.SetCount(pixelDmxConfiguration.GetGroups(), nActivePorts, false);

	const auto nTestPattern = static_cast<pixelpatterns::Pattern>(pixelDmxParams.GetTestPattern());
	PixelTestPattern pixelTestPattern(nTestPattern, nActivePorts);

	pixelDmxMulti.Print();

	pp.SetOutput(&pixelDmxMulti);
	pp.Print();

#if defined (NODE_RDMNET_LLRP_ONLY)
	display.TextStatus(RDMNetConst::MSG_CONFIG, CONSOLE_YELLOW);

	char aDescription[rdm::personality::DESCRIPTION_MAX_LENGTH + 1];
	snprintf(aDescription, sizeof(aDescription) - 1, "PixelPusher %u-%s:%d", nActivePorts, pixel::pixel_get_type(pixelDmxConfiguration.GetType()), pixelDmxConfiguration.GetCount());

	char aLabel[RDM_DEVICE_LABEL_MAX_LENGTH + 1];
	const auto nLength = snprintf(aLabel, sizeof(aLabel) - 1, GD32_BOARD_NAME " PixelPusher");

	RDMPersonality *pPersonalities[1] = { new RDMPersonality(aDescription, nullptr) };
	RDMNetDevice llrpOnlyDevice(pPersonalities, 1);

	llrpOnlyDevice.SetLabel(RDM_ROOT_DEVICE, aLabel, static_cast<uint8_t>(nLength));
	llrpOnlyDevice.SetProductCategory(E120_PRODUCT_CATEGORY_FIXTURE);
	llrpOnlyDevice.SetProductDetail(E120_PRODUCT_DETAIL_LED);
	llrpOnlyDevice.Init();

	RDMDeviceParams rdmDeviceParams;

	rdmDeviceParams.Load();
	rdmDeviceParams.Set(&llrpOnlyDevice);

	llrpOnlyDevice.Print();
#endif

	display.SetTitle("PixelPusher %d", nActivePorts);
	display.Set(2, displayudf::Labels::VERSION);
	display.Set(3, displayudf::Labels::HOSTNAME);
	display.Set(4, displayudf::Labels::IP);
	display.Set(5, displayudf::Labels::DEFAULT_GATEWAY);
	display.Set(6, displayudf::Labels::BOARDNAME);

	DisplayUdfParams displayUdfParams;

	displayUdfParams.Load();
	displayUdfParams.Set(&display);

	display.Show();
	display.Printf(7, "%s:%d G%d %s",
		pixel::pixel_get_type(pixelDmxConfiguration.GetType()),
		pixelDmxConfiguration.GetCount(),
		pixelDmxConfiguration.GetGroupingCount(),
		pixel::pixel_get_map(pixelDmxConfiguration.GetMap()));

	if (nTestPattern != pixelpatterns::Pattern::NONE) {
		display.ClearLine(6);
		display.Printf(6, "%s:%u", PixelPatterns::GetName(nTestPattern), static_cast<uint32_t>(nTestPattern));
	}

	RemoteConfig remoteConfig(remoteconfig::Node::PP, remoteconfig::Output::PIXEL, nActivePorts);

	RemoteConfigParams remoteConfigParams;
	remoteConfigParams.Load();
	remoteConfigParams.Set(&remoteConfig);

	while (configStore.Flash())
		;

	mDns.Print();

	display.TextStatus("Starting PixelPusher", CONSOLE_YELLOW);

	pp.Start();

	display.TextStatus("PixelPusher Started", CONSOLE_GREEN);

	hw.WatchdogInit();

	for (;;) {
		hw.WatchdogFeed();
		nw.Run();
		pp.Run();
		remoteConfig.Run();
		configStore.Flash();
		pixelTestPattern.Run();
		mDns.Run();
#if defined (ENABLE_NTP_CLIENT)
		ntpClient.Run();
#endif
#if defined (NODE_RDMNET_LLRP_ONLY)
		llrpOnlyDevice.Run();
#endif
		display.Run();
		hw.Run();
	}
}
