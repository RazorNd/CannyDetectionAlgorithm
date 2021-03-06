
# Canny Detection Algorithm

Это программа детектирующая границы в изображении с помощью [алгоритма Кенни](https://ru.wikipedia.org/wiki/%D0%9E%D0%BF%D0%B5%D1%80%D0%B0%D1%82%D0%BE%D1%80_%D0%9A%D1%8D%D0%BD%D0%BD%D0%B8).

[![Build Status](https://travis-ci.org/RazorNd/CannyDetectionAlgorithm.svg?branch=master)](https://travis-ci.org/RazorNd/CannyDetectionAlgorithm)
[![GitHub release](https://img.shields.io/github/release/RazorNd/CannyDetectionAlgorithm.svg)](https://github.com/RazorNd/CannyDetectionAlgorithm/releases)
[![license](https://img.shields.io/github/license/RazorNd/CannyDetectionAlgorithm.svg)](https://github.com/RazorNd/CannyDetectionAlgorithm/blob/master/LICENSE)
[![Created by RazorNd](https://img.shields.io/badge/Created%20by-RazorNd-orange.svg)](https://github.com/RazorNd)

# Структура и алгоритм

Проект разбит на следующие модули:

  * **common** - разделяемая библиотека с общей реализацией алгоритма Кенни.
  * **CannyQtWrapper** - разделяемая библеотека выступающая оберткой над общей библеотекой **common** для использования фич Qt (сигналы и слоты).
  * **Simple** - исполняемый файл, простая *GUI* программа используящая библиотеку **CannyQtWrapper** для демонстрации возможностей алгоритма Кенни.

Описание работы алгоритма описана в разделе [документации](docs/README.md).

# Установка

Скачайте код используя git:

```bash
git clone https://github.com/RazorNd/CannyDetectionAlgorithm.git
```

Или перейдите в раздел [Релизы](https://github.com/RazorNd/CannyDetectionAlgorithm/releases) и скачайте актуальную версию исходных кодов.

# Требования

Для сборки и использования проекта необходим фреймворк **Qt 5**.

# Сборка

Сборка происходит с помощью **qmake**.

Чтобы собрать проект перейдите в корневой католог проекта.

Создайте директорию сборки и перейдите в нее:

```bash
mkdir build
cd build
```

Запустите **qmake** передав ему в качестве параметров проектный файл. После чего запустите `make all`. 
Для максимального использования многоядерного процессора добавьте параметр `make all -j n`, где n - это колличество ядер процессора + 1.

```bash
qmake ..
make all -j 5
```

Завершающий этап установки это перемещение всех зависимостей:

```bash
make install
```

# Запуск

Перейдите в католог сборки *Simple* и запусти бинарный файл `Simple`.
