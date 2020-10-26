// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdio.h>

#include "context.h"
#include "hid.h"
#include "payload.h"
#include "protocol.h"
#include "syscall.h"

int iptsd_data_handle_input(struct iptsd_context *iptsd)
{
	struct ipts_data *header = (struct ipts_data *)iptsd->data;

	int ret = 0;

	switch (header->type) {
	case IPTS_DATA_TYPE_PAYLOAD:
		ret = iptsd_payload_handle_input(iptsd, header);
		break;
	case IPTS_DATA_TYPE_HID_REPORT:
		ret = iptsd_hid_handle_input(iptsd, header);
		break;
	}

	if (ret < 0) {
		fprintf(stderr, "Failed to parse data: %s",
				iptsd_syscall_strerr(ret));
	}

	return ret;
}
