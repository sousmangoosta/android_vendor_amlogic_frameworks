/*
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *  @author   tellen
 *  @version  1.0
 *  @date     2013/04/26
 *  @par function description:
 *  - 1 write property or sysfs from native to java service
 */

#define LOG_TAG "ISystemControl"
//#define LOG_NDEBUG 0

#include <utils/Log.h>
#include <stdint.h>
#include <sys/types.h>
#include <binder/Parcel.h>
#include <ISystemControlService.h>

namespace android {

class BpSystemControlService : public BpInterface<ISystemControlService>
{
public:
    BpSystemControlService(const sp<IBinder>& impl)
        : BpInterface<ISystemControlService>(impl)
    {
    }

	virtual bool getProperty(const String16& key, String16& value)
	{
		Parcel data, reply;
        data.writeInterfaceToken(ISystemControlService::getInterfaceDescriptor());
        data.writeString16(key);
        ALOGV("getProperty key:%s\n", String8(key).string());

        if (remote()->transact(GET_PROPERTY, data, &reply) != NO_ERROR) {
            ALOGD("getProperty could not contact remote\n");
            return false;
        }

        int32_t err = reply.readInt32();
        if (err == 0) {
            ALOGE("getProperty caught exception %d\n", err);
            return false;
        }
        value = reply.readString16();
        return true;
	}

	virtual bool getPropertyString(const String16& key, String16& def, String16& value)
	{
		Parcel data, reply;
        data.writeInterfaceToken(ISystemControlService::getInterfaceDescriptor());
        data.writeString16(key);
        data.writeString16(def);
		ALOGV("getPropertyString key:%s\n", String8(key).string());

        if (remote()->transact(GET_PROPERTY_STRING, data, &reply) != NO_ERROR) {
            ALOGD("getPropertyString could not contact remote\n");
            return false;
        }

        int32_t err = reply.readInt32();
        if (err == 0) {
            ALOGE("getPropertyString caught exception %d\n", err);
            return false;
        }

        value = reply.readString16();
        return true;
	}

	virtual int32_t getPropertyInt(const String16& key, int32_t def)
	{
		Parcel data, reply;
        data.writeInterfaceToken(ISystemControlService::getInterfaceDescriptor());
        data.writeString16(key);
        data.writeInt32(def);
		ALOGV("getPropertyInt key:%s\n", String8(key).string());

        if (remote()->transact(GET_PROPERTY_INT, data, &reply) != NO_ERROR) {
            ALOGE("getPropertyInt could not contact remote\n");
            return -1;
        }

        return reply.readInt32();
	}

	virtual int64_t getPropertyLong(const String16& key, int64_t def)
	{
		Parcel data, reply;
        data.writeInterfaceToken(ISystemControlService::getInterfaceDescriptor());
        data.writeString16(key);
        data.writeInt64(def);
		ALOGV("getPropertyLong key:%s\n", String8(key).string());

        if (remote()->transact(GET_PROPERTY_LONG, data, &reply) != NO_ERROR) {
            ALOGE("getPropertyLong could not contact remote\n");
            return -1;
        }

        return reply.readInt64();
	}

	virtual bool getPropertyBoolean(const String16& key, bool def)
	{
		Parcel data, reply;
        data.writeInterfaceToken(ISystemControlService::getInterfaceDescriptor());
        data.writeString16(key);
        data.writeInt32(def?1:0);

		ALOGV("getPropertyBoolean key:%s\n", String8(key).string());

        if (remote()->transact(GET_PROPERTY_BOOL, data, &reply) != NO_ERROR) {
            ALOGE("getPropertyBoolean could not contact remote\n");
            return false;
        }

        return reply.readInt32() != 0;
	}

	virtual void setProperty(const String16& key, const String16& value)
	{
		Parcel data, reply;
        data.writeInterfaceToken(ISystemControlService::getInterfaceDescriptor());
        data.writeString16(key);
		data.writeString16(value);
		ALOGV("setProperty key:%s, value:%s\n", String8(key).string(), String8(value).string());

        if (remote()->transact(SET_PROPERTY, data, &reply) != NO_ERROR) {
            ALOGE("setProperty could not contact remote\n");
            return;
        }
	}

	virtual bool readSysfs(const String16& path, String16& value)
	{
		Parcel data, reply;
        data.writeInterfaceToken(ISystemControlService::getInterfaceDescriptor());
        data.writeString16(path);
		ALOGV("setProperty path:%s\n", String8(path).string());

        if (remote()->transact(READ_SYSFS, data, &reply) != NO_ERROR) {
            ALOGE("readSysfs could not contact remote\n");
            return false;
        }

        value = reply.readString16();
        return true;
	}

	virtual bool writeSysfs(const String16& path, const String16& value)
	{
		Parcel data, reply;
        data.writeInterfaceToken(ISystemControlService::getInterfaceDescriptor());
        data.writeString16(path);
		data.writeString16(value);
		ALOGV("writeSysfs path:%s, value:%s\n", String8(path).string(), String8(value).string());

        if (remote()->transact(WRITE_SYSFS, data, &reply) != NO_ERROR) {
            ALOGE("writeSysfs could not contact remote\n");
            return false;
        }

        return reply.readInt32() != 0;
	}


    virtual bool getBootEnv(const String16& key, String16& value)
	{
		Parcel data, reply;
        data.writeInterfaceToken(ISystemControlService::getInterfaceDescriptor());
        data.writeString16(key);
        ALOGV("getBootEnv key:%s\n", String8(key).string());

        if (remote()->transact(GET_BOOT_ENV, data, &reply) != NO_ERROR) {
            ALOGD("getBootEnv could not contact remote\n");
            return false;
        }

        int32_t err = reply.readInt32();
        if (err == 0) {
            ALOGE("getBootEnv caught exception %d\n", err);
            return false;
        }
        value = reply.readString16();
        return true;
	}

    virtual void setBootEnv(const String16& key, const String16& value)
	{
		Parcel data, reply;
        data.writeInterfaceToken(ISystemControlService::getInterfaceDescriptor());
        data.writeString16(key);
		data.writeString16(value);
		ALOGV("setBootEnv key:%s, value:%s\n", String8(key).string(), String8(value).string());

        if (remote()->transact(SET_BOOT_ENV, data, &reply) != NO_ERROR) {
            ALOGE("setBootEnv could not contact remote\n");
            return;
        }
	}
};

IMPLEMENT_META_INTERFACE(SystemControlService, "droidlogic.ISystemControlService");

// ----------------------------------------------------------------------------

status_t BnISystemControlService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch(code) {
        case GET_PROPERTY: {
            CHECK_INTERFACE(ISystemControlService, data, reply);
            String16 value;
            bool result = getProperty(data.readString16(), value);
            reply->writeInt32(result);
            reply->writeString16(value);
            return NO_ERROR;
        }
        case GET_PROPERTY_STRING: {
            CHECK_INTERFACE(ISystemControlService, data, reply);
            String16 key = data.readString16();
            String16 def = data.readString16();
            String16 value;
            bool result = getPropertyString(key, def, value);
            reply->writeInt32(result);
            reply->writeString16(value);
            return NO_ERROR;
        }
        case GET_PROPERTY_INT: {
            CHECK_INTERFACE(ISystemControlService, data, reply);
            String16 key = data.readString16();
            int32_t def = data.readInt32();
            int result = getPropertyInt(key, def);
            reply->writeInt32(result);
            return NO_ERROR;
        }
        case GET_PROPERTY_LONG: {
            CHECK_INTERFACE(ISystemControlService, data, reply);
            String16 key = data.readString16();
            int64_t def = data.readInt64();

            int64_t result = getPropertyLong(key, def);
            reply->writeInt64(result);
            return NO_ERROR;
        }
        case GET_PROPERTY_BOOL: {
            CHECK_INTERFACE(ISystemControlService, data, reply);

            String16 key = data.readString16();
            int32_t def = data.readInt32();
            bool result = getPropertyBoolean(key, (def!=0));
            reply->writeInt32(result?1:0);
            return NO_ERROR;
        }
        case SET_PROPERTY: {
            CHECK_INTERFACE(ISystemControlService, data, reply);
            String16 key = data.readString16();
            String16 val = data.readString16();
            setProperty(key, val);
            return NO_ERROR;
        }
        case READ_SYSFS: {
            CHECK_INTERFACE(ISystemControlService, data, reply);
            String16 sys = data.readString16();
            String16 value;
            readSysfs(sys, value);
            reply->writeString16(value);
            return NO_ERROR;
        }
        case WRITE_SYSFS: {
            CHECK_INTERFACE(ISystemControlService, data, reply);
            String16 sys = data.readString16();
            String16 value = data.readString16();
            bool result = writeSysfs(sys, value);
            reply->writeInt32(result?1:0);
            return NO_ERROR;
        }
        case GET_BOOT_ENV: {
            CHECK_INTERFACE(ISystemControlService, data, reply);
            String16 value;
            bool result = getBootEnv(data.readString16(), value);
            reply->writeInt32(result);
            reply->writeString16(value);
            return NO_ERROR;
        }
        case SET_BOOT_ENV: {
            CHECK_INTERFACE(ISystemControlService, data, reply);
            String16 key = data.readString16();
            String16 val = data.readString16();
            setBootEnv(key, val);
            return NO_ERROR;
        }
        default: {
            return BBinder::onTransact(code, data, reply, flags);
        }
    }
    // should be unreachable
    return NO_ERROR;
}

}; // namespace android
