﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LU20_correctors_ctrl
{
    class QueueElement
    {
        int _id;
        int _reg_addr;
        public int id
        {
            get { return _id; }
            set { _id = value; }
        }
        public int reg_addr
        {
            get { return _reg_addr; }
            set { _reg_addr = value; }
        }

        public QueueElement(int id_in, int reg_addr_in)
        {
            id = id_in;
            reg_addr = reg_addr_in;
        }

        public virtual byte[] get_modbus_cmd()
        {
            return new byte[] { 0 };
        }
        //public int id;
    }

    class QueueElementR : QueueElement
    {
        int _rd_cnt;
        public QueueElementR(int id_in, int reg_addr_in, int rd_cnt_in) : base(id_in, reg_addr_in)
        {
            rd_cnt = rd_cnt_in;
        }

        public int rd_cnt
        {
            get { return _rd_cnt; }
            set { _rd_cnt = value; }
        }

        public override byte[] get_modbus_cmd()
        {
            modbus_rtu_helper modbus = new modbus_rtu_helper();
            var modbus_cmd = modbus.build_rhr_cmd((byte)id, (ushort)reg_addr, (ushort)rd_cnt);
            return modbus_cmd;
        }
    }

    class QueueElementW : QueueElement
    {
        int _reg_data;

        public int reg_data
        {
            get { return _reg_data; }
            set { _reg_data = value; }
        }

        public QueueElementW(int id_in, int reg_addr_in, int reg_data_in)
            : base(id_in, reg_addr_in)
        {
            reg_data = reg_data_in;
        }

        public override byte[] get_modbus_cmd()
        {
            modbus_rtu_helper modbus = new modbus_rtu_helper();
            var modbus_cmd = modbus.build_wsr_cmd((byte)id, (ushort)reg_addr, (ushort)reg_data);
            return modbus_cmd;
        }
    }


}
