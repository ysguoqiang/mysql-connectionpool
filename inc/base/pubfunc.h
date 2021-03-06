#ifndef __PUBFUNC_H__
#define __PUBFUNC_H__

#include "base/stringUtils.h"
#include <string>
#include <vector>
#include <iostream>
#include "base/CoreException.h"
__USING_WILLOW_NS
using namespace std;

#define exstrcpy(dest_array, source) estrncpy(dest_array, source, #dest_array, #source, __FILE__, __LINE__)
//#define  CopyToCharArray
/**
  * Description     : 类似strncpy，不同的是如果源字符串长度超出预期时直接抛异常并打印日志
  * @param[out] dest    : 目标字符串（调用成功或者抛出异常时存放的是以\0结尾的字符串）
  * @param[in] source   : 源字符串
  * @param[in] dest_name        : 源字符串含义，默认为dest，如果不关心可不填
  * @param[in] source_name      : 目标字符串含义，默认为source，如果不关心可不填
  * @return         : 目标字符串长度
  * @note           : 效率较低，建议只在服务中使用
  * @exception      : 如果源字符串长度超过目标字符串最大字符数，则出抛出stl异常exception。如果len为0也会抛异常
  */
template<int BufferSize>
inline int estrncpy(char (&dest)[BufferSize], const char*source,
             const char *dest_name = "dest",
             const char *source_name = "source", const char *filename = "", int line = 0)
{
    //只有一个字符的数组没意义
    base_static_assert( BufferSize > 1 );

    size_t i;
    //复制source内容到dest中，最多复制len个字符
    for (i = 0; i < BufferSize && (source[i] != '\0'); i++)
    {
        dest[i] = source[i];
    }

    //未溢出，末尾加上\0
    if (i != BufferSize)
    {
        dest[i] = '\0';
        //BASE_LOG_DEBUG("%s=[%s]", dest_name, dest);
    }
    else
    {
        //如果复制了BufferSize个字符仍然未碰上\0
        //标记字符串结束
        dest[ (int) BufferSize - 1 ] = '\0';
        char errbuf[1024];
        sprintf(errbuf, "源字符串[%s]长度超出预期! 目标字符串[%s]最大空间为[%d]！",
            source_name, dest_name, (int) BufferSize);
			
        throw CoreException(errbuf);
    }

    return (int) i;
}

#endif