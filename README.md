# BDMedicalApp

- Добавление/удаление/поиск пациентов в базе данных
- Добавление/удаление изображений к пациентам
- Создание/Редактирование/Удаление комментариев, описания к изображениям, разметкам
- Создание(Отрисовка)/Удаление разметок к изображениям пациента

# Главное окно (пациенты)
  ![alt text](https://pp.userapi.com/c852024/v852024825/8d677/5hpQwYDwbAk.jpg)
# Изображения пациента (комментарии)
  ![alt text](https://pp.userapi.com/c852024/v852024825/8d68e/hXjD0vFSU6w.jpg)
# Изображения пациента (создание разметок)
  ![alt text](https://pp.userapi.com/c852024/v852024825/8d6b1/vSyZpn1dr8w.jpg)
# Разметки изображения
  ![alt text](https://pp.userapi.com/c852024/v852024825/8d6a2/zptdrwmarqc.jpg)

## Описание файлов

  -     main.cpp - входная точка в программу 
  -     mainwindow.h - Контроллер главного окна программы
  -     Managers/databasemanager.h - Менеджер базы данных
  -     Managers/Helpers/queryripper.h - Генератор запросов MySQL + парсер моделей
  -     Common/magic.h - Файл с "Магией" - синтаксический сахар
  -     appcore.h - Связующая сущность (ядро) между UI и другими сервисами, основной делигат
  -     Common/Models/entity.h - Базовый класс всех моделей сущностей
  -     Common/Models/patientmodel.h - Модель сущности пациента
  -     Common/Models/imagemodel.h - Модель сущности изображения пациента
  -     Common/Models/markmodel.h - Модель сущности разметки изображения пациента
  -     patientinputform.h - Форма для ввода нового пациента
  -     appmodel.h - Менеджер стандартных моделей приложения
  -     Common/consts.h - Константы приложения
  -     imageeditor.h - Кастомный QGraphicsView для рисования
  -     searchform.h - Форма для поиска (фильтра) пациентов
  
  
  
