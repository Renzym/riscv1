`ifndef RISCV_PKG_SV
`define RISCV_PKG_SV

package riscv_pkg;

    typedef struct packed {
        int unsigned addr;
        bit [31:0]   value;
    } reg_expect_t;

    localparam int REGRESSION_N = 19;

    const reg_expect_t REGRESSION_EXPECTS[19] = '{
        '{1,  32'd5},
        '{2,  32'd10},
        '{3,  32'd15},
        '{4,  32'd15},
        '{5,  32'd0},
        '{6,  32'd28},
        '{7,  32'd36},
        '{8,  32'h12345000},
        '{9,  32'd48},
        '{14, 32'h000000ab},
        '{15, 32'h000000cd},
        '{16, 32'hffffffcd},
        '{17, 32'hffffff80},
        '{21, 32'hffffbee0},
        '{22, 32'h0000bee0},
        '{23, 32'hffffbee0},
        '{26, 32'd100},
        '{27, 32'd16},
        '{28, 32'd1}
    };

    function automatic string reg_name(int unsigned addr);
        return $sformatf("x%0d", addr);
    endfunction

    const int unsigned DEFAULT_RUN_CYCLES = 150;

endpackage

`endif
