#include "HugoUtils/HugoString.h"

const std::vector<std::wstring>& HugoUtils::FreezeApiInvalidStrings::GetCorrectStrings() {
	static const std::vector<std::wstring> correctStrings = {
		// 系统运行正常，获取磁盘信息成功"
		L"\u7cfb\u7edf\u8fd0\u884c\u6b63\u5e38\uff0c\u83b7\u53d6\u78c1\u76d8\u4fe1\u606f\u6210\u529f\"",
		// 检测到系统有潜藏病毒暴露，请使用杀毒软件清除完系统病毒后，再冻结保护"
		L"\u68c0\u6d4b\u5230\u7cfb\u7edf\u6709\u6f5c\u85cf\u75c5\u6bd2\u66b4\u9732\uff0c\u8bf7\u4f7f"
		L"\u7528\u6740\u6bd2\u8f6f\u4ef6\u6e05\u9664\u5b8c\u7cfb\u7edf\u75c5\u6bd2\u540e\uff0c"
		L"\u518d\u51bb\u7ed3\u4fdd\u62a4\"",
		// 检测到系统运行时过于卡顿，请使用安全卫士清理好系统环境后，再冻结保护"
		L"\u68c0\u6d4b\u5230\u7cfb\u7edf\u8fd0\u884c\u65f6\u8fc7\u4e8e\u5361\u987f\uff0c\u8bf7\u4f7f"
		L"\u7528\u5b89\u5168\u536b\u58eb\u6e05\u7406\u597d\u7cfb\u7edf\u73af\u5883\u540e\uff0c"
		L"\u518d\u51bb\u7ed3\u4fdd\u62a4\"",
		// 检测到零度内核已经运行中，但由于某种异常导致其没有进入重定向还原环节"
		L"\u68c0\u6d4b\u5230\u96f6\u5ea6\u5185\u6838\u5df2\u7ecf\u8fd0\u884c\u4e2d\uff0c"
		L"\u4f46\u7531\u4e8e\u67d0\u79cd\u5f02\u5e38\u5bfc\u81f4\u5176\u6ca1\u6709\u8fdb\u5165\u91cd"
		L"\u5b9a\u5411\u8fd8\u539f\u73af\u8282\"",
		// 检测到零度内核状态异常"
		L"\u68c0\u6d4b\u5230\u96f6\u5ea6\u5185\u6838\u72b6\u6001\u5f02\u5e38\"",
		// 检测到零度内核未知异常"
		L"\u68c0\u6d4b\u5230\u96f6\u5ea6\u5185\u6838\u672a\u77e5\u5f02\u5e38\"",
		// 希沃冰点"
		L"\u5e0c\u6c83\u51b0\u70b9\"",
		// 正在运行"
		L"\u6b63\u5728\u8fd0\u884c\"",
		// 请稍后重试"
		L"\u8bf7\u7a0d\u540e\u91cd\u8bd5\"",
		// 系统磁盘类型不支持冰冻"
		L"\u7cfb\u7edf\u78c1\u76d8\u7c7b\u578b\u4e0d\u652f\u6301\u51b0\u51bb\"",
		// 系统有未完成更新项，请更新系统后再设置冰点"
		L"\u7cfb\u7edf\u6709\u672a\u5b8c\u6210\u66f4\u65b0\u9879\uff0c\u8bf7\u66f4\u65b0\u7cfb\u7edf"
		L"\u540e\u518d\u8bbe\u7f6e\u51b0\u70b9\"",
		// 不支持动态磁盘，请重新分区后再冰冻"
		L"\u4e0d\u652f\u6301\u52a8\u6001\u78c1\u76d8\uff0c\u8bf7\u91cd\u65b0\u5206\u533a\u540e\u518d\u51b0\u51bb\"",
		// 检测到系统关键文件存在文件系统压缩，请解除压缩后重试"
		L"\u68c0\u6d4b\u5230\u7cfb\u7edf\u5173\u952e\u6587\u4ef6\u5b58\u5728\u6587\u4ef6\u7cfb\u7edf\u538b\u7f29\uff0c"
		L"\u8bf7\u89e3\u9664\u538b\u7f29\u540e\u91cd\u8bd5\"",
		// 不支持继续冰冻，请解冻重启后再冰冻"
		L"\u4e0d\u652f\u6301\u7ee7\u7eed\u51b0\u51bb\uff0c\u8bf7\u89e3\u51bb\u91cd\u542f\u540e\u518d\u51b0\u51bb\"",
		// 为保证系统稳定性，至少需保证一个非系统盘不被冰冻"
		L"\u4e3a\u4fdd\u8bc1\u7cfb\u7edf\u7a33\u5b9a\u6027\uff0c"
		L"\u81f3\u5c11\u9700\u4fdd\u8bc1\u4e00\u4e2a\u975e\u7cfb\u7edf\u76d8\u4e0d\u88ab\u51b0\u51bb\"",
		// 请释放磁盘空间后再试"
		L"\u8bf7\u91ca\u653e\u78c1\u76d8\u7a7a\u95f4\u540e\u518d\u8bd5\"",
		// 未知错误"
		L"\u672a\u77e5\u9519\u8bef\""
	};
	return correctStrings;
}

void HugoUtils::FreezeApiInvalidStrings::FixInvalidFreezeStrings(std::wstring& response) {
	const auto& correctStrings = GetCorrectStrings();
	size_t pos = 0;
	while (pos < response.size()) {
		bool matched = false;
		for (const auto& s : correctStrings) {
			const size_t minLen = (s.length() > 3) ? (s.length() - 3) : 1;
			for (size_t len = s.length(); len >= minLen; --len) {
				if (pos + len <= response.size() &&
					response.compare(pos, len, s, 0, len) == 0) {
					response.replace(pos, len, s);
					size_t after = pos + s.length();
					while (after < response.size() && response[after] == L'?') {
						response.erase(after, 1);
					}
					pos += s.length();
					matched = true;
					break;
				}
			}
			if (matched) break;
		}
		if (!matched) {
			++pos;
		}
	}
}