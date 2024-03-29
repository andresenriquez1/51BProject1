// Copyright © 2019-2023
// 
// Licensed under the Apache License;
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <stdint.h>
#include <bitset>
#include <queue>
#include <unordered_map>
#include <stringutil.h>
#include <simobject.h>
#include <util.h>
#include "uuid_gen.h"
#include "debug.h"
#include "config.h"

namespace tinyrv {

typedef uint8_t Byte;
typedef uint32_t Word;
typedef int32_t  WordI;
typedef uint64_t DWord;
typedef int64_t  DWordI;
typedef uint32_t WordF;

typedef std::bitset<MAX_NUM_REGS> RegMask;

typedef std::unordered_map<uint32_t, uint32_t> CSRs;

///////////////////////////////////////////////////////////////////////////////

enum class RegType {
  None,
  Integer,
  Float
};

inline std::ostream &operator<<(std::ostream &os, const RegType& type) {
  switch (type) {
  case RegType::None: break;
  case RegType::Integer: os << "x"; break;  
  case RegType::Float:   os << "f"; break;
  default: assert(false);
  }
  return os;
}

///////////////////////////////////////////////////////////////////////////////

enum class ExeType {
  ALU,
  LSU,
  CSR,
  ExeTypeCount
};

inline std::ostream &operator<<(std::ostream &os, const ExeType& type) {
  switch (type) {
  case ExeType::ALU: os << "ALU"; break;
  case ExeType::LSU: os << "LSU"; break;
  case ExeType::CSR: os << "CSR"; break;
  default: assert(false);
  }
  return os;
}

///////////////////////////////////////////////////////////////////////////////

enum class AluType {
  ARITH,
  BRANCH,
  SYSCALL,
  IMUL,
  IDIV
};

inline std::ostream &operator<<(std::ostream &os, const AluType& type) {
  switch (type) {
  case AluType::ARITH:   os << "ARITH"; break;
  case AluType::BRANCH:  os << "BRANCH"; break;
  case AluType::SYSCALL: os << "SYSCALL"; break;
  case AluType::IMUL:    os << "IMUL"; break;
  case AluType::IDIV:    os << "IDIV"; break;
  default: assert(false);
  }
  return os;
}

///////////////////////////////////////////////////////////////////////////////

enum class LsuType {
  LOAD,
  STORE,
  FENCE
};

inline std::ostream &operator<<(std::ostream &os, const LsuType& type) {
  switch (type) {
  case LsuType::LOAD:  os << "LOAD"; break;
  case LsuType::STORE: os << "STORE"; break;
  default: assert(false);
  }
  return os;
}

///////////////////////////////////////////////////////////////////////////////

enum class AddrType {
  Global,
  IO
};

inline std::ostream &operator<<(std::ostream &os, const AddrType& type) {
  switch (type) {
  case AddrType::Global: os << "Global"; break;
  case AddrType::IO:     os << "IO"; break;
  default: assert(false);
  }
  return os;
}

inline AddrType get_addr_type(uint64_t addr) {
  if (addr >= IO_BASE_ADDR) {
     return AddrType::IO;
  }
  return AddrType::Global;
}

///////////////////////////////////////////////////////////////////////////////

struct mem_addr_size_t {
  uint64_t addr;
  uint32_t size;
};

///////////////////////////////////////////////////////////////////////////////

enum class CSRType {
  CSRRW,
  CSRRS,
  CSRRC
};

inline std::ostream &operator<<(std::ostream &os, const CSRType& type) {
  switch (type) {
  case CSRType::CSRRW: os << "CSRRW"; break;
  case CSRType::CSRRS: os << "CSRRS"; break;
  case CSRType::CSRRC: os << "CSRRC"; break;
  default: assert(false);
  }
  return os;
}

}
