CXX = g++
CXXFLAGS = -std=c++20 -Wall -g -I.. -I../lab_3

# Тесты для 3 лабораторной
TESTS = Complex_test.exe Matrix_test.exe Quete_test.exe Set_test.exe

.PHONY: all clean run run_matrix run_set run_queue run_complex

all: $(TESTS)

# Тест комплексных чисел
Complex_test.exe: Complex_test.cpp
	$(CXX) $(CXXFLAGS) -D CATCH_CONFIG_MAIN $< -o $@

# Тест матрицы
Matrix_test.exe: Matrix_test.cpp
	$(CXX) $(CXXFLAGS) -D CATCH_CONFIG_MAIN $< -o $@

# Тест очереди
Quete_test.exe: Quete_test.cpp
	$(CXX) $(CXXFLAGS) -D CATCH_CONFIG_MAIN $< -o $@

# Тест множества
Set_test.exe: Set_test.cpp
	$(CXX) $(CXXFLAGS) -D CATCH_CONFIG_MAIN $< -o $@

# Запуск всех тестов
run: $(TESTS)
	@echo ""
	@echo "=== Запуск всех тестов ==="
	@for test in $(TESTS); do \
		echo ""; \
		echo "=== $$test ==="; \
		./$$test; \
	done

# Запуск отдельных тестов
run_complex: Complex_test.exe
	@echo "=== Тесты комплексных чисел ==="
	./Complex_test.exe

run_matrix: Matrix_test.exe
	@echo "=== Тесты матрицы ==="
	./Matrix_test.exe

run_queue: Quete_test.exe
	@echo "=== Тесты очереди ==="
	./Quete_test.exe

run_set: Set_test.exe
	@echo "=== Тесты множества ==="
	./Set_test.exe

# Очистка (Windows)
clean:
	del *.exe 2> nul

# Очистка (Linux/Mac)
clean_nix:
	rm -f $(TESTS)

# Перекомпиляция и запуск
rebuild: clean all run

# Помощь
help:
	@echo "Доступные команды:"
	@echo "  make           - скомпилировать все тесты"
	@echo "  make run       - скомпилировать и запустить все тесты"
	@echo "  make run_complex - запустить тесты комплексных чисел"
	@echo "  make run_matrix - запустить тесты матрицы"
	@echo "  make run_queue  - запустить тесты очереди"
	@echo "  make run_set    - запустить тесты множества"
	@echo "  make clean     - удалить .exe файлы (Windows)"
	@echo "  make rebuild   - перекомпилировать и запустить"