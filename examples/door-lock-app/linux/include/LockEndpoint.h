/*
 *
 *    Copyright (c) 2022 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

#include <app/clusters/door-lock-server/door-lock-server.h>
#include <vector>

struct LockUserInfo;
struct LockCredentialInfo;
struct WeekDaysScheduleInfo;
struct YearDayScheduleInfo;

static constexpr size_t DOOR_LOCK_CREDENTIAL_INFO_MAX_DATA_SIZE = 20;

class LockEndpoint
{
public:
    LockEndpoint(chip::EndpointId endpointId, uint16_t numberOfLockUsersSupported, uint16_t numberOfCredentialsSupported,
                 uint8_t weekDaySchedulesPerUser, uint8_t yearDaySchedulesPerUser) :
        mEndpointId(endpointId),
        mLockState(DlLockState::kLocked), mLockUsers(numberOfLockUsersSupported),
        mLockCredentials(numberOfCredentialsSupported + 1),
        mWeekDaySchedules(numberOfLockUsersSupported, std::vector<WeekDaysScheduleInfo>(weekDaySchedulesPerUser)),
        mYearDaySchedules(numberOfLockUsersSupported, std::vector<YearDayScheduleInfo>(numberOfLockUsersSupported))
    {}

    inline chip::EndpointId GetEndpointId() { return mEndpointId; }

    bool Lock(const Optional<chip::ByteSpan> & pin);
    bool Unlock(const Optional<chip::ByteSpan> & pin);

    bool GetUser(uint16_t userIndex, EmberAfPluginDoorLockUserInfo & user) const;
    bool SetUser(uint16_t userIndex, chip::FabricIndex creator, chip::FabricIndex modifier, const chip::CharSpan & userName,
                 uint32_t uniqueId, DlUserStatus userStatus, DlUserType usertype, DlCredentialRule credentialRule,
                 const DlCredential * credentials, size_t totalCredentials);

    bool GetCredential(uint16_t credentialIndex, DlCredentialType credentialType,
                       EmberAfPluginDoorLockCredentialInfo & credential) const;

    bool SetCredential(uint16_t credentialIndex, DlCredentialStatus credentialStatus, DlCredentialType credentialType,
                       const chip::ByteSpan & credentialData);

    DlStatus GetSchedule(uint8_t weekDayIndex, uint16_t userIndex, EmberAfPluginDoorLockWeekDaySchedule & schedule);
    DlStatus GetSchedule(uint8_t yearDayIndex, uint16_t userIndex, EmberAfPluginDoorLockYearDaySchedule & schedule);
    DlStatus SetSchedule(uint8_t weekDayIndex, uint16_t userIndex, DlScheduleStatus status, DlDaysMaskMap daysMask,
                         uint8_t startHour, uint8_t startMinute, uint8_t endHour, uint8_t endMinute);
    DlStatus SetSchedule(uint8_t yearDayIndex, uint16_t userIndex, DlScheduleStatus status, uint32_t localStartTime,
                         uint32_t localEndTime);

private:
    bool setLockState(DlLockState lockState, const Optional<chip::ByteSpan> & pin);
    const char * lockStateToString(DlLockState lockState) const;

    chip::EndpointId mEndpointId;
    DlLockState mLockState;

    // This is very naive implementation of users/credentials/schedules database and by no means the best practice. Proper storage
    // of those items is out of scope of this example.
    std::vector<LockUserInfo> mLockUsers;
    std::vector<LockCredentialInfo> mLockCredentials;
    std::vector<std::vector<WeekDaysScheduleInfo>> mWeekDaySchedules;
    std::vector<std::vector<YearDayScheduleInfo>> mYearDaySchedules;
};

struct LockUserInfo
{
    char userName[DOOR_LOCK_USER_NAME_BUFFER_SIZE];
    DlCredential credentials[DOOR_LOCK_MAX_CREDENTIALS_PER_USER];
    size_t totalCredentials;
    uint32_t userUniqueId;
    DlUserStatus userStatus;
    DlUserType userType;
    DlCredentialRule credentialRule;
    chip::FabricIndex createdBy;
    chip::FabricIndex lastModifiedBy;
};

struct LockCredentialInfo
{
    DlCredentialStatus status;
    DlCredentialType credentialType;
    uint8_t credentialData[DOOR_LOCK_CREDENTIAL_INFO_MAX_DATA_SIZE];
    size_t credentialDataSize;
};

struct WeekDaysScheduleInfo
{
    DlScheduleStatus status;
    EmberAfPluginDoorLockWeekDaySchedule schedule;
};

struct YearDayScheduleInfo
{
    DlScheduleStatus status;
    EmberAfPluginDoorLockYearDaySchedule schedule;
};
