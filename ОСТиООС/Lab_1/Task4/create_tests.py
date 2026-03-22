# create_tests.py
# Создаёт три тестовых файла для проверки всех режимов программы

def write_bin(filename, data):
    """Записывает массив байтов в бинарный файл"""
    with open(filename, 'wb') as f:
        f.write(bytes(data))
    print(f"✅ Файл '{filename}' создан.")

# 1. Тест для xor8: XOR всех байтов
# Байты: 0x01, 0x02, 0x03, 0x04
# Ожидаем: 0x01 ^ 0x02 ^ 0x03 ^ 0x04 = 0x04
xor8_data = [0x01, 0x02, 0x03, 0x04]
write_bin("test_xor8.bin", xor8_data)

# 2. Тест для xorodd: XOR 4-байтных блоков, где хотя бы один байт — простое число
# Простые числа (в диапазоне байта): 2, 3, 5, 7, 11, 13, ...
xorodd_data = [
    0x02, 0x00, 0x00, 0x00,  # 0x00000002 — содержит 2 → простое → участвует
    0x01, 0x04, 0x06, 0x08,  # нет простых → пропускаем
    0x03, 0xFF, 0xFF, 0xFF,  # содержит 3 → простое → участвует
    0x08, 0x09, 0x0A, 0x0B,  # 11 (0x0B) — простое → участвует
]
write_bin("test_xorodd.bin", xorodd_data)

# 3. Тест для mask: проверка соответствия маске
# Два 4-байтных числа в little-endian:
#   - 0xDEADBEEF → записываем как [0xEF, 0xBE, 0xAD, 0xDE]
#   - 0x12345678 → [0x78, 0x56, 0x34, 0x12]
mask_data = [
    0xEF, 0xBE, 0xAD, 0xDE,  # 0xDEADBEEF
    0x78, 0x56, 0x34, 0x12,  # 0x12345678
]
write_bin("test_mask.bin", mask_data)

print("\n🎉 Все тестовые файлы успешно созданы!")
print("Теперь можно проверить программу:")
print("  ./main test_xor8.bin xor8")
print("  ./main test_xorodd.bin xorodd")
print("  ./main test_mask.bin mask DEAD")