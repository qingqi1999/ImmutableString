1. objectId、clientId 等在多个地方作为key使用。
2. 这些id不可变
3. 这些id在多个线程被使用到
4. 但到处都没有使用这个字符串的时候，将其清理掉，防止内存泄漏
5. 支持作为 unorderd_map 的key使用