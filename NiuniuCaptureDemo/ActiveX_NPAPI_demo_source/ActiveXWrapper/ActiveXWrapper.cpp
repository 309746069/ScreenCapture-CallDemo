// ActiveXWrapper.cpp : DLL 导出的实现。


#include "stdafx.h"
#include "resource.h"
#include "ActiveXWrapper.h"

HINSTANCE gl_hInstance1;
class CActiveXWrapperModule : public CAtlDllModuleT< CActiveXWrapperModule >
{
public :
	DECLARE_LIBID(LIBID_ActiveXWrapperLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ACTIVEXWRAPPER, "{DE0BA92D-CA93-494D-8A8D-7E84D05F899F}")
};

CActiveXWrapperModule _AtlModule;


#ifdef _MANAGED
#pragma managed(push, off)
#endif

// DLL 入口点
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	gl_hInstance1 = hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved); 
}

#ifdef _MANAGED
#pragma managed(pop)
#endif




// 用于确定 DLL 是否可由 OLE 卸载
STDAPI DllCanUnloadNow(void)
{
    return _AtlModule.DllCanUnloadNow();
}


// 返回一个类工厂以创建所请求类型的对象
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - 将项添加到系统注册表
STDAPI DllRegisterServer(void)
{
    // 注册对象、类型库和类型库中的所有接口
    HRESULT hr = _AtlModule.DllRegisterServer();
	return hr;
}


// DllUnregisterServer - 将项从系统注册表中移除
STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}

