// Copyright (c) YugaByte, Inc.

#ifndef ENT_SRC_YB_MASTER_TS_DESCRIPTOR_H
#define ENT_SRC_YB_MASTER_TS_DESCRIPTOR_H

#include "yb/util/shared_ptr_tuple.h"

namespace yb {

namespace consensus {
class ConsensusServiceProxy;
}

namespace tserver {
class TabletServerAdminServiceProxy;
class TabletServerServiceProxy;
class TabletServerBackupServiceProxy;
}

namespace master {
namespace enterprise {

typedef util::SharedPtrTuple<tserver::TabletServerAdminServiceProxy,
    tserver::TabletServerServiceProxy,
    tserver::TabletServerBackupServiceProxy,
    consensus::ConsensusServiceProxy> ProxyTuple;

} // namespace enterprise
} // namespace master
} // namespace yb

#include "../../../../src/yb/master/ts_descriptor.h"

namespace yb {
namespace master {
namespace enterprise {

class TSDescriptor : public yb::master::TSDescriptor {
  typedef yb::master::TSDescriptor super;
 public:
  explicit TSDescriptor(const std::string& perm_id) : super(perm_id) {}
  virtual ~TSDescriptor() {}

  const string& GetPlacementUuid() const {
    std::lock_guard<simple_spinlock> l(lock_);
    return placement_uuid_;
  }

 protected:
  CHECKED_STATUS RegisterUnlocked(const NodeInstancePB& instance,
                                  const TSRegistrationPB& registration) override;

 private:
  string placement_uuid_;
};

} // namespace enterprise
} // namespace master
} // namespace yb

#endif // ENT_SRC_YB_MASTER_TS_DESCRIPTOR_H