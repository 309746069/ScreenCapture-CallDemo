========================================================================
    �ģ��⣺ActiveXWrapper ��Ŀ����
========================================================================

Ӧ�ó�������Ϊ�������˴� ActiveXWrapper ��Ŀ���������ڴ˻���֮��
��д�Լ��Ķ�̬���ӿ� (DLL)��


���ļ������������Ŀ��ÿ���ļ�
�����ݡ�

ActiveXWrapper.vcproj
    ����ʹ��Ӧ�ó��������ɵ� VC++ ��Ŀ������Ŀ�ļ��� 
    �������й����ɸ��ļ���ʹ�õ� Visual C++ �汾����Ϣ���Լ�
    �й���Ӧ�ó�������ѡ���ƽ̨�����ú���Ŀ����
    ����Ϣ��

ActiveXWrapper.idl
    ���ļ�������������Ŀ�ж�������Ϳ⡢�ӿ�
    �� coclass �� IDL ���塣
    ���ļ����� MIDL ���������������ɣ�
        C++ �ӿڶ���� GUID ����                 (ActiveXWrapper.h)
        GUID ����                                (ActiveXWrapper_i.c)
        һ�����Ϳ�                               (ActiveXWrapper.tlb)
        ���ʹ���                                 (ActiveXWrapper_p.c �� dlldata.c)

ActiveXWrapper.h
    ���ļ������� ActiveXWrapper.idl �ж������� C++ �ӿڶ���
    �� GUID �����������ڱ���������� MIDL �������ɡ�

ActiveXWrapper.cpp
    ���ļ���������ӳ��� DLL ������ʵ�֡�

ActiveXWrapper.rc
    ���ǳ���ʹ�õ����� Microsoft Windows ��Դ����
    ����

ActiveXWrapper.def
    ��ģ�鶨���ļ�Ϊ�������ṩ�й� DLL ��Ҫ���
    ��������Ϣ�������������������ݵĵ�����
        DllGetClassObject  
        DllCanUnloadNow    
        GetProxyDllInfo    
        DllRegisterServer	
        DllUnregisterServer

/////////////////////////////////////////////////////////////////////////////
������׼�ļ���

StdAfx.h��StdAfx.cpp
    ��Щ�ļ�����������Ϊ ActiveXWrapper.pch ��Ԥ����ͷ (PCH) �ļ�
    ����Ϊ StdAfx.obj ��Ԥ���������ļ���

Resource.h
    �������ڶ�����Դ ID �ı�׼ͷ�ļ���

/////////////////////////////////////////////////////////////////////////////
����/��� (stub) DLL ��Ŀ��ģ�鶨���ļ���

ActiveXWrapperps.vcproj
    ���ļ����������ɴ���/��� (stub) DLL ����Ŀ�ļ������б�Ҫ����
	����Ŀ�е� IDL �ļ��������ٰ���һ���ӿڣ�����
	�����ɴ���/��� (stub) DLL ֮ǰ�����ȱ��� IDL �ļ���	�˽�������
	dlldata.c��ActiveXWrapper_i.c �� ActiveXWrapper_p.c�����ǡ�
	�����ɴ���/��� (stub) DLL ������ġ�

ActiveXWrapperps.def
    ��ģ�鶨���ļ�Ϊ�������ṩ�йش���/��� (stub) ��Ҫ���
    ��������Ϣ��

/////////////////////////////////////////////////////////////////////////////
