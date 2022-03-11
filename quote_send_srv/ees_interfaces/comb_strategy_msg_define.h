
#pragma once 
#include <string.h>
#include "eqs_define.h"
#include <assert.h>

#pragma pack(push, 1)


// 客户下的组合策略单 
struct tmcs_new_comb_order_req
{

};

// 内核给的组合策略接受
struct tmhs_comb_order_snapshot
{

};

// 内核给的组合策略市场接受
struct tmhs_comb_order_exch_accept
{

};

// 内核给的组合策略市场拒绝 
struct tmhs_comb_order_exch_reject
{
	
};

// 内核给的组合策略成交
struct tmhs_comb_order_exec
{

};

// 内核给客户端的组合订单接受
struct tmhc_comb_order_accept
{

};


// 内核给客户端的组合订单拒绝
struct tmhc_comb_order_reject
{

};

// 内核给客户的组合订单成交
struct tmhc_comb_order_exec
{

};





#pragma pack(pop)
