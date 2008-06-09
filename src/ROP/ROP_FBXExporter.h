/*
 * PROPRIETARY INFORMATION.  This software is proprietary to
 * Side Effects Software Inc., and is not to be reproduced,
 * transmitted, or disclosed in any way without written permission.
 *
 * Produced by:
 *	Oleg Samus
 *	Side Effects
 *	123 Front Street West
 *	Toronto, Ontario
 *	Canada   M5V 3E7
 *	416-504-9876
 *
 * NAME:	ROP library (C++)
 *
 * COMMENTS:	FBX output
 *
 */

#ifndef __ROP_FBXExporter_h__
#define __ROP_FBXExporter_h__

#include "ROP_API.h"
#include "ROP_FBXCommon.h"

#include "ROP_FBXErrorManager.h"

#ifdef UT_DEBUG
#include <UT/UT_Debug.h>
#endif

class FBX_FILMBOX_NAMESPACE::KFbxSdkManager;
class FBX_FILMBOX_NAMESPACE::KFbxScene;
class ROP_FBXNodeManager;
class ROP_FBXActionManager;
class UT_Interrupt;

typedef vector < char* > TCharPtrVector;
/********************************************************************************************************/
// Note: When adding public members, make sure to add an equivalent to dummy exporter for cases when FBX is
// disabled.
class ROP_API ROP_FBXExporter
{
public:
    ROP_FBXExporter();
    ~ROP_FBXExporter();

    // These are responsible for the actual conversion process.
    bool initializeExport(const char* output_name, float tstart, float tend, ROP_FBXExportOptions* options);
    void doExport(void);
    bool finishExport(void);

    KFbxSdkManager* getSDKManager(void);
    KFbxScene* getFBXScene(void);
    ROP_FBXErrorManager* getErrorManager(void);
    ROP_FBXNodeManager* getNodeManager(void);
    ROP_FBXActionManager* getActionManager(void);

    ROP_FBXExportOptions* getExportOptions(void);
    const char* getOutputFileName(void);

    float getStartTime(void);
    float getEndTime(void);
    bool getExportingAnimation(void);

    void queueStringToDeallocate(char* string_ptr);
    KFbxNode* GetFBXRootNode(OP_Node* asking_node);
    UT_Interrupt* GetBoss(void);

    static UT_String* getVersions(void);

private:
    void deallocateQueuedStrings(void);

private:

    ROP_FBXExportOptions myExportOptions;

    KFbxSdkManager* mySDKManager;
    KFbxScene* myScene;
    ROP_FBXErrorManager* myErrorManager;
    ROP_FBXNodeManager* myNodeManager;
    ROP_FBXActionManager* myActionManager;

    string myOutputFile;

    float myStartTime, myEndTime;

    TCharPtrVector myStringsToDeallocate;
    KFbxNode* myDummyRootNullNode;

    UT_Interrupt	*myBoss;
    bool myDidCancel;

#ifdef UT_DEBUG
    // Timing variables
    double myDBStartTime, myDBEndTime;
#endif
};
/********************************************************************************************************/
#endif
