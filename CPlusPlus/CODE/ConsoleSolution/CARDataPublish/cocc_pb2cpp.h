#ifndef COCC_PB2CPP_H
#define COCC_PB2CPP_H

#include "../Common/proto_cocc_cats_tunnel.pb.h"
#include "cocc_publish_data.h"
// ���ݽṹת��

// �г�ȫ����Ϣ
void PB2CPPTrianIndicationInit(const pbproto::post_cbtc_train_indication_init& pb, pubdata::post_cbtc_train_indication_init& cpp);
// �г�������Ϣ
void PB2CPPTrianBlockInfo(const pbproto::post_train_block_info& pb, pubdata::post_train_block_info& cpp);
#endif
