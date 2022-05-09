/**
*  @file sin_entity.h
*  @brief ？？？的适配接口
*  @author taoxinyu
*  @date 11/16/2021
*  @version initial version
*  Copyright Shanghai Baosight Software Co., Ltd.
*/
#ifndef SIN_ENTITY_H
#define SIN_ENTITY_H

#ifdef _WIN32
#	ifdef BSILRE_ENTITY_EXPORTS
#		define SIN_ENTITY __declspec(dllexport)
#	else
#		define SIN_ENTITY __declspec(dllimport)
#	endif
#else
#	define BSILRE_ENTITY
#endif

namespace sin_entity {

	class SIN_ENTITY Entity {
		// 启动接口
		void start();
		// 停止所有线程
		void stop();
		// 做一些有趣的事情
		void do_something();
	};
}// namespaceSIN_entity

#endif