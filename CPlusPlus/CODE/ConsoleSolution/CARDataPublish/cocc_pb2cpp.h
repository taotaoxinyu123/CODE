#ifndef COCC_PB2CPP_H
#define COCC_PB2CPP_H

#include "../Common/proto_cocc_cats_tunnel.pb.h"
#include "cocc_publish_data.h"
// 数据结构转换

// 列车全体消息
void PB2CPPTrianIndicationInit(const pbproto::post_cbtc_train_indication_init& pb, pubdata::post_cbtc_train_indication_init& cpp);
// 列车阻塞消息
void PB2CPPTrianBlockInfo(const pbproto::post_train_block_info& pb, pubdata::post_train_block_info& cpp);
#endif
