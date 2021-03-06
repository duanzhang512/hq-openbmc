#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <syslog.h>
#include <openbmc/ipmb.h>
#include <openbmc/libgpio.h>
#include "pal.h"


static int
bmc_ipmb_swap_info_process(uint8_t ipmi_cmd, uint8_t netfn, uint8_t t_bmc_addr,
                               uint8_t *txbuf, uint8_t txlen,
                               uint8_t *rxbuf, uint8_t *rxlen ) {
  int ret = 0;
  uint16_t m_bmc_addr;

  ret = pal_get_bmc_ipmb_slave_addr(&m_bmc_addr, BMC_IPMB_BUS_ID);
  if(ret != 0) {
    return ret;
  }

  return lib_ipmb_send_request(ipmi_cmd, netfn,
                               txbuf, txlen,
                               rxbuf, rxlen,
                               BMC_IPMB_BUS_ID, t_bmc_addr, m_bmc_addr);
}

int
cmd_set_smbc_restore_power_policy(uint8_t policy, uint8_t t_bmc_addr) {
  uint8_t ipmi_cmd = CMD_OEM_SET_POWER_POLICY;
  uint8_t netfn = NETFN_OEM_REQ;
  uint8_t tbuf[8];
  uint8_t rbuf[8] = {0x00};
  uint8_t rlen;
  uint8_t tlen;

  tbuf[0] = policy;
  tlen = 1;

  return bmc_ipmb_swap_info_process(ipmi_cmd, netfn, t_bmc_addr, tbuf, tlen, rbuf, &rlen);
}

int
cmd_smbc_chassis_ctrl(uint8_t cmd, uint8_t t_bmc_addr) {
  uint8_t ipmi_cmd = CMD_CHASSIS_CONTROL;
  uint8_t netfn = NETFN_CHASSIS_REQ;
  uint8_t tbuf[8];
  uint8_t rbuf[8] = {0x00};
  uint8_t rlen;
  uint8_t tlen;

  tbuf[0] = cmd;
  tlen = 1;

  return bmc_ipmb_swap_info_process(ipmi_cmd, netfn, t_bmc_addr, tbuf, tlen, rbuf, &rlen);
}

int
cmd_smbc_get_glbcpld_ver(uint8_t t_bmc_addr, uint8_t *ver) {
  uint8_t ipmi_cmd = CMD_APP_MASTER_WRITE_READ;
  uint8_t netfn = NETFN_APP_REQ;
  uint8_t tbuf[8] = {0x2f, 0xaa, 0x04, 0x00, 0x10, 0x00, 0x28}; // bus 23, addr 0x55
  uint8_t rbuf[8] = {0x00};
  uint8_t rlen;
  uint8_t tlen = 7;
  int ret;

  ret = bmc_ipmb_swap_info_process(ipmi_cmd, netfn, t_bmc_addr, tbuf, tlen, rbuf, &rlen);
  if (!ret) {
    memcpy(ver, rbuf, 4);
  }

  return ret;
}
