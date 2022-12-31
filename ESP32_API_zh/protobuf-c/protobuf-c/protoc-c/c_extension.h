// 协议缓冲区-Google的数据交换格式
// 版权所有2008谷歌公司。保留所有权利。
// http://code.google.com/p/protobuf/
//
// 以源代码和二进制形式重新分发和使用，无论有无
// 如果满足以下条件，则允许进行修改
// 遇见：
//
//     *源代码的重新分发必须保留上述版权
// 注意，此条件列表和以下免责声明。
//     *二进制形式的重新分发必须复制上述内容
// 版权声明、本条件列表和以下免责声明
// 随
// 分配
//     *既没有谷歌公司的名称，也没有谷歌公司
// 贡献者可用于支持或推广源自
// 本软件未经事先书面许可。
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// 作者：kenton@google.com（Kenton Varda）
//  基于原始协议缓冲区设计
//  Sanjay Ghemawat、Jeff Dean和其他人。

// 版权所有（c）2008-2013，Dave Benson。保留所有权利。
//
// 以源代码和二进制形式重新分发和使用，无论有无
// 如果满足以下条件，则允许进行修改
// 遇见：
//
//     *源代码的重新分发必须保留上述版权
// 注意，此条件列表和以下免责声明。
//
//     *二进制形式的重新分发必须复制上述内容
// 版权声明、本条件列表和以下免责声明
// 随
// 分配
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// DaveBenson修改为实现C代码。

#ifndef GOOGLE_PROTOBUF_COMPILER_C_EXTENSION_H__
#define GOOGLE_PROTOBUF_COMPILER_C_EXTENSION_H__

#include <string>
#include <google/protobuf/stubs/common.h>

namespace google {
namespace protobuf {
  class FieldDescriptor;       // 描述符.h
  namespace io {
    class Printer;             // 打印机.h
  }
}

namespace protobuf {
namespace compiler {
namespace c {

// 为扩展生成代码，该扩展可能在某些
// 消息或可能在文件范围内。这比FieldGenerator简单得多
// 因为扩展只是具有有趣类型的简单标识符。
class ExtensionGenerator {
 public:
  // 参见发电机。cc表示dllexport_decl的含义。
  explicit ExtensionGenerator(const FieldDescriptor* descriptor,
                              const string& dllexport_decl);
  ~ExtensionGenerator();

  // 标题内容。
  void GenerateDeclaration(io::Printer* printer);

  // 源文件内容。
  void GenerateDefinition(io::Printer* printer);

 private:
  const FieldDescriptor* descriptor_;
  string type_traits_;
  string dllexport_decl_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ExtensionGenerator);
};

}  // 命名空间c
}  // 命名空间编译器
}  // 命名空间protobuf

}  // 名称空间google
#endif  // GOOGLE_PROTOBUF_COMPILER_C_MESSAGE_H__

