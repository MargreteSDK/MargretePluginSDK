// MargretePLuginSDK
// Copyright (c) 2024 inonote
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php

#pragma once
#include <memory.h>
#include <stdint.h>

typedef uint32_t MpResult;
typedef int MpBoolean;
typedef int MpInteger;

#define MP_SDK_VERSION 1

#define MP_TRUE 1
#define MP_FALSE 0

#define MP_DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
	static const MpGuid IID_##name = { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } };

struct MpGuid {
	unsigned long  data1;
	unsigned short data2;
	unsigned short data3;
	unsigned char  data4[8];

	bool operator==(const MpGuid& iid) const { return memcmp(this, &iid, sizeof(this)) == 0; }
	bool operator!=(const MpGuid& iid) const { return operator!=(iid); }
};

struct MP_PLUGININFO {
	MpInteger sdkVersion;
	wchar_t* nameBuffer;
	MpInteger nameBufferLength;
	wchar_t* descBuffer;
	MpInteger descBufferLength;
	wchar_t* developerBuffer;
	MpInteger developerBufferLength;
};



// {B2F76848-FB04-4CFC-9E5A-B5E4FD4747CA}
MP_DEFINE_GUID(IMargretePluginBase,
	0xb2f76848, 0xfb04, 0x4cfc, 0x9e, 0x5a, 0xb5, 0xe4, 0xfd, 0x47, 0x47, 0xca);

class IMargretePluginBase {
public:
	virtual MpInteger addRef() = 0;
	virtual MpInteger release() = 0;
	virtual MpBoolean queryInterface(const MpGuid& iid, void** ppobj) = 0;
};



// {E9200B48-FEE7-4332-9811-E4B63B96508F}
MP_DEFINE_GUID(IMargretePluginUndoBuffer,
	0xe9200b48, 0xfee7, 0x4332, 0x98, 0x11, 0xe4, 0xb6, 0x3b, 0x96, 0x50, 0x8f);

class IMargretePluginUndoBuffer : public IMargretePluginBase {
public:
	virtual MpInteger addRef() = 0;
	virtual MpInteger release() = 0;
	virtual MpBoolean queryInterface(const MpGuid& iid, void** ppobj) = 0;

	virtual MpBoolean beginRecording() = 0;
	virtual MpBoolean commitRecording() = 0;
	virtual MpBoolean discardRecording() = 0;
	virtual MpBoolean undo() = 0;
	virtual MpBoolean redo() = 0;
	virtual MpBoolean canUndo() const = 0;
	virtual MpBoolean canRedo() const = 0;
	virtual MpBoolean isRecording() const = 0;
};



#define MP_NOTETYPE_UNKNOWN 0
#define MP_NOTETYPE_TAP 1
#define MP_NOTETYPE_EXTAP 2
#define MP_NOTETYPE_FLICK 3
#define MP_NOTETYPE_DAMAGE 4
#define MP_NOTETYPE_HOLD 5
#define MP_NOTETYPE_SLIDE 6
#define MP_NOTETYPE_AIR 7
#define MP_NOTETYPE_AIRHOLD 8
#define MP_NOTETYPE_AIRSLIDE 9
#define MP_NOTETYPE_AIRCRUSH 10
#define MP_NOTETYPE_CLICK 11
#define MP_NOTETYPE_LAST 13

#define MP_NOTELONGATTR_NONE 0
#define MP_NOTELONGATTR_BEGIN 1
#define MP_NOTELONGATTR_STEP 2
#define MP_NOTELONGATTR_CONTROL 3
#define MP_NOTELONGATTR_CURVE_CONTROL 4
#define MP_NOTELONGATTR_END 5
#define MP_NOTELONGATTR_END_NOACT 6

#define MP_NOTEDIR_NONE 0
#define MP_NOTEDIR_AUTO 1
#define MP_NOTEDIR_UP 2
#define MP_NOTEDIR_DOWN 3
#define MP_NOTEDIR_CENTER 4
#define MP_NOTEDIR_LEFT 5
#define MP_NOTEDIR_RIGHT 6
#define MP_NOTEDIR_UPLEFT 7
#define MP_NOTEDIR_UPRIGHT 8
#define MP_NOTEDIR_DOWNLEFT 9
#define MP_NOTEDIR_DOWNRIGHT 10
#define MP_NOTEDIR_ROTATE_LEFT 11
#define MP_NOTEDIR_ROTATE_RIGHT 12
#define MP_NOTEDIR_INOUT 13
#define MP_NOTEDIR_OUTIN 14

#define MP_NOTEEXATTR_NONE 0
#define MP_NOTEEXATTR_INVERT 1
#define MP_NOTEEXATTR_HAS_NOTE 2
#define MP_NOTEEXATTR_EXJDG 3

struct MP_NOTEINFO {
	MpInteger type; // MP_NOTETYPE_
	MpInteger longAttr; // MP_NOTELONGATTR_
	MpInteger direction; // MP_NOTEDIR_
	MpInteger exAttr; // MP_NOTEEXATTR_
	MpInteger variationId;
	MpInteger x;
	MpInteger width;
	MpInteger height;
	MpInteger tick;
	MpInteger timelineId;
};

// {7BF6174E-DDF7-498C-AE30-A92DCE2B94D9}
MP_DEFINE_GUID(IMargretePluginNote,
	0x7bf6174e, 0xddf7, 0x498c, 0xae, 0x30, 0xa9, 0x2d, 0xce, 0x2b, 0x94, 0xd9);

class IMargretePluginNote : public IMargretePluginBase {
public:
	virtual MpInteger addRef() = 0;
	virtual MpInteger release() = 0;
	virtual MpBoolean queryInterface(const MpGuid& iid, void** ppobj) = 0;

	virtual MpInteger getId() const = 0;

	virtual void getInfo(MP_NOTEINFO* noteInfo) const = 0;
	virtual void setInfo(const MP_NOTEINFO* noteInfo) = 0;
	virtual MpInteger getChildrenCount() const = 0;
	virtual MpBoolean getChild(MpInteger index, IMargretePluginNote** ppobj) const = 0;
	virtual MpBoolean getParent(IMargretePluginNote** ppobj) const = 0;

	virtual MpBoolean appendChild(IMargretePluginNote* note) = 0;
	virtual MpBoolean deleteChild(IMargretePluginNote* child) = 0;
	virtual MpBoolean clone(IMargretePluginNote** ppobj) const = 0;
	virtual void replaceWith(const IMargretePluginNote* srcNote, MpBoolean requiresSort) = 0;
	virtual void copyInfoTo(IMargretePluginNote* destNote) const = 0;
	virtual MpBoolean getBaseNote(IMargretePluginNote** ppobj) const = 0;

	virtual void offsetChild(MpInteger offsetTick) = 0;
	virtual void flipH(MpBoolean recrusive) = 0;
};



// {4607AA39-1AD7-4FAE-900F-D786953E2F1F}
MP_DEFINE_GUID(IMargretePluginEvent,
	0x4607aa39, 0x1ad7, 0x4fae, 0x90, 0xf, 0xd7, 0x86, 0x95, 0x3e, 0x2f, 0x1f);

class IMargretePluginEvent : public IMargretePluginBase {
public:
	virtual MpInteger addRef() = 0;
	virtual MpInteger release() = 0;
	virtual MpBoolean queryInterface(const MpGuid& iid, void** ppobj) = 0;

	virtual MpInteger getId() const = 0;
};



struct MP_EVENT_TLSINFO {
	MpInteger timelineId;
	MpInteger tick;
	double speed;
};

// {8A7C2E24-F055-4F41-A7A4-2F7369E633FE}
MP_DEFINE_GUID(IMargretePluginEventTimelineSpeed,
	0x8a7c2e24, 0xf055, 0x4f41, 0xa7, 0xa4, 0x2f, 0x73, 0x69, 0xe6, 0x33, 0xfe);

class IMargretePluginEventTimelineSpeed : public IMargretePluginEvent {
public:
	virtual MpInteger addRef() = 0;
	virtual MpInteger release() = 0;
	virtual MpBoolean queryInterface(const MpGuid& iid, void** ppobj) = 0;

	virtual MpInteger getId() const = 0;

	virtual void getInfo(MP_EVENT_TLSINFO* tlsInfo) const = 0;
	virtual void setInfo(const MP_EVENT_TLSINFO* tlsInfo) = 0;

	virtual void replaceWith(const IMargretePluginEventTimelineSpeed* srcEvent) = 0;
	virtual void copyInfoTo(IMargretePluginEventTimelineSpeed* destEvent) const = 0;
};



struct MP_EVENT_NSMINFO {
	MpInteger tick;
	double speed;
};

// {8A7C2E24-F055-4F41-A7A4-2F7369E633FE}
MP_DEFINE_GUID(IMargretePluginEventNoteSpeedModifier,
	0xf1656785, 0x2f74, 0x4efb, 0x8a, 0xbb, 0x90, 0x16, 0x94, 0xe, 0xfa, 0xd1);

class IMargretePluginEventNoteSpeedModifier : public IMargretePluginEvent {
public:
	virtual MpInteger addRef() = 0;
	virtual MpInteger release() = 0;
	virtual MpBoolean queryInterface(const MpGuid& iid, void** ppobj) = 0;

	virtual MpInteger getId() const = 0;

	virtual void getInfo(MP_EVENT_NSMINFO* nsmInfo) const = 0;
	virtual void setInfo(const MP_EVENT_NSMINFO* nsmInfo) = 0;

	virtual void replaceWith(const IMargretePluginEventNoteSpeedModifier* srcEvent) = 0;
	virtual void copyInfoTo(IMargretePluginEventNoteSpeedModifier* destEvent) const = 0;
};



struct MP_EVENT_BPMINFO {
	MpInteger tick;
	double bpm;
};

// {8A7C2E24-F055-4F41-A7A4-2F7369E633FE}
MP_DEFINE_GUID(IMargretePluginEventBpm,
	0xd25bee92, 0xca99, 0x4d62, 0xa9, 0x61, 0x26, 0xbf, 0xfd, 0x5b, 0x6e, 0xee);

class IMargretePluginEventBpm : public IMargretePluginEvent {
public:
	virtual MpInteger addRef() = 0;
	virtual MpInteger release() = 0;
	virtual MpBoolean queryInterface(const MpGuid& iid, void** ppobj) = 0;

	virtual MpInteger getId() const = 0;

	virtual void getInfo(MP_EVENT_BPMINFO* bpmInfo) const = 0;
	virtual void setInfo(const MP_EVENT_BPMINFO* bpmInfo) = 0;

	virtual void replaceWith(const IMargretePluginEventBpm* srcEvent) = 0;
	virtual void copyInfoTo(IMargretePluginEventBpm* destEvent) const = 0;
};



struct MP_EVENT_BCINFO {
	MpInteger bar;
	MpInteger beatsPerBar;
	MpInteger beatUnit;
};

// {8A7C2E24-F055-4F41-A7A4-2F7369E633FE}
MP_DEFINE_GUID(IMargretePluginEventBeatChange,
	0xf4c8269e, 0xc08, 0x46a8, 0x96, 0xf6, 0xf2, 0xaa, 0xaf, 0x78, 0x64, 0x2d);

class IMargretePluginEventBeatChange : public IMargretePluginEvent {
public:
	virtual MpInteger addRef() = 0;
	virtual MpInteger release() = 0;
	virtual MpBoolean queryInterface(const MpGuid& iid, void** ppobj) = 0;

	virtual MpInteger getId() const = 0;

	virtual void getInfo(MP_EVENT_BCINFO* bcInfo) const = 0;
	virtual void setInfo(const MP_EVENT_BCINFO* bcInfo) = 0;

	virtual void replaceWith(const IMargretePluginEventBeatChange* srcEvent) = 0;
	virtual void copyInfoTo(IMargretePluginEventBeatChange* destEvent) const = 0;
};



// {6DB9DD3F-631B-4496-BF5B-535FF1F0EEB0}
MP_DEFINE_GUID(IMargretePluginChart,
	0x6db9dd3f, 0x631b, 0x4496, 0xbf, 0x5b, 0x53, 0x5f, 0xf1, 0xf0, 0xee, 0xb0);

class IMargretePluginChart : public IMargretePluginBase {
public:
	virtual MpInteger addRef() = 0;
	virtual MpInteger release() = 0;
	virtual MpBoolean queryInterface(const MpGuid& iid, void** ppobj) = 0;

	virtual MpBoolean createNote(IMargretePluginNote** ppobj) const = 0;
	virtual MpInteger getNotesCount() const = 0;
	virtual MpBoolean getNote(MpInteger index, IMargretePluginNote** ppobj) = 0;
	virtual MpBoolean appendNote(IMargretePluginNote* note) = 0;
	virtual MpBoolean deleteNote(IMargretePluginNote* note) = 0;
	virtual void offsetNotes(MpInteger tick) = 0;
	
	virtual MpBoolean createEvent(const MpGuid& iid, void** ppobj) const = 0;
	virtual MpBoolean appendEvent(IMargretePluginEvent* ppobj) = 0;
	virtual MpBoolean deleteEvent(IMargretePluginEvent* ppobj) = 0;
	virtual MpBoolean findEventTimelineSpeed(MpInteger tick, MpInteger timelineId, void** ppobj) = 0;
	virtual MpBoolean findEventNoteSpeedModifier(MpInteger tick, void** ppobj) = 0;
	virtual MpBoolean findEventBpm(MpInteger tick, void** ppobj) = 0;
	virtual MpBoolean findEventBeatChange(MpInteger bar, void** ppobj) = 0;
};



// {F90DCE72-71CA-412D-94CE-B4AE89FE5A12}
MP_DEFINE_GUID(IMargretePluginDocument,
	0xf90dce72, 0x71ca, 0x412d, 0x94, 0xce, 0xb4, 0xae, 0x89, 0xfe, 0x5a, 0x12);

class IMargretePluginDocument : public IMargretePluginBase {
public:
	virtual MpInteger addRef() = 0;
	virtual MpInteger release() = 0;
	virtual MpBoolean queryInterface(const MpGuid& iid, void** ppobj) = 0;

	virtual MpBoolean getChart(IMargretePluginChart** ppobj) = 0;
	virtual MpBoolean getUndoBuffer(IMargretePluginUndoBuffer** ppobj) = 0;
};



// {577C993C-679C-4ECD-B205-31C64E574DB2}
MP_DEFINE_GUID(IMargretePluginContext,
	0x577c993c, 0x679c, 0x4ecd, 0xb2, 0x5, 0x31, 0xc6, 0x4e, 0x57, 0x4d, 0xb2);

class IMargretePluginContext : public IMargretePluginBase {
public:
	virtual MpInteger addRef() = 0;
	virtual MpInteger release() = 0;
	virtual MpBoolean queryInterface(const MpGuid& iid, void** ppobj) = 0;

	virtual MpBoolean getDocument(IMargretePluginDocument** ppobj) = 0;
	virtual void* getMainWindowHandle() = 0;
	virtual MpInteger getCurrentTick() const = 0;
	virtual void update() const = 0;
};



// {2E868DB6-FF3A-46C8-9609-18EA41947D42}
MP_DEFINE_GUID(IMargretePluginCommand,
	0x2e868db6, 0xff3a, 0x46c8, 0x96, 0x9, 0x18, 0xea, 0x41, 0x94, 0x7d, 0x42);

class IMargretePluginCommand : public IMargretePluginBase {
public:
	virtual MpInteger addRef() = 0;
	virtual MpInteger release() = 0;
	virtual MpBoolean queryInterface(const MpGuid& iid, void** ppobj) = 0;

	virtual MpBoolean getCommandName(wchar_t* text, MpInteger textLength) const = 0;
	virtual MpBoolean invoke(IMargretePluginContext* ctx) = 0;
};



typedef void(_stdcall* tMargretePluginGetInfo)(MP_PLUGININFO*);
typedef MpBoolean (_stdcall* tMargretePluginCommandCreate)(IMargretePluginCommand**);



template<typename T>
class MargreteComPtr {
public:
	MargreteComPtr() {}

	MargreteComPtr(T* ptr) {
		m_ptr = ptr;
	}

	MargreteComPtr(const MargreteComPtr<T>& x) {
		m_ptr = x.m_ptr;
		m_ptr->addRef();
	}

	MargreteComPtr(MargreteComPtr<T>&& x) noexcept {
		m_ptr = x.m_ptr;
		x.m_ptr = nullptr;
	}

	~MargreteComPtr() {
		if (m_ptr)
			m_ptr->release();
	}

	void reset() {
		if (m_ptr)
			m_ptr->release();
		m_ptr = nullptr;
	}

	void reset(T* ptr) {
		reset();
		m_ptr = ptr;
	}

	T* get() const {
		return m_ptr;
	}

	T** put() {
		return &m_ptr;
	}
	
	void** putVoid() {
		return (void**)&m_ptr;
	}

	MpBoolean clonePointer(T** ppobj) const {
		if (!m_ptr || !ppobj)
			return MP_FALSE;
		m_ptr->addRef();
		*ppobj = m_ptr;
		return MP_TRUE;
	}

	T* operator->() const {
		return get();
	}

	T& operator*() const {
		return *get();
	}

	bool operator!() const {
		return !m_ptr;
	}

	void** operator&() {
		return putVoid();
	}

private:
	T* m_ptr = nullptr;
};
