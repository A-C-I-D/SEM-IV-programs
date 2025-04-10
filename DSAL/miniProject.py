# Design a mini project for automated Term work assessment of student based on parameters like daily attendance, Unit Test / Prelim performance, students achievements if any, Mock Practical

import json

class Student:
    def __init__(self, name, roll_no, attendance, unit_test_score, achievements, mock_practical_score):
        self.name = name
        self.roll_no = roll_no
        self.attendance = attendance
        self.unit_test_score = unit_test_score
        self.achievements = achievements
        self.mock_practical_score = mock_practical_score
        self.term_work_score = 0

    def calculate_term_work_score(self):
        # Weights for different parameters
        attendance_weight = 0.3
        unit_test_weight = 0.4
        achievements_weight = 0.1
        mock_practical_weight = 0.2

        # Validating and normalizing scores
        self.attendance = min(max(self.attendance, 0), 100)  # Attendance (0-100%)
        self.unit_test_score = min(max(self.unit_test_score, 0), 100)  # Unit Test (0-100)
        self.achievements = min(max(self.achievements, 0), 10)  # Achievements (0-10)
        self.mock_practical_score = min(max(self.mock_practical_score, 0), 50)  # Mock Practical (0-50)

        # Calculating term work score
        self.term_work_score = (
            (self.attendance * attendance_weight) +
            (self.unit_test_score * unit_test_weight) +
            (self.achievements * achievements_weight * 10) +  # Scaling achievements to match 100 points
            (self.mock_practical_score * mock_practical_weight * 2)  # Scaling mock practical to match 100 points
        )

    def to_dict(self):
        return {
            "name": self.name,
            "roll_no": self.roll_no,
            "attendance": self.attendance,
            "unit_test_score": self.unit_test_score,
            "achievements": self.achievements,
            "mock_practical_score": self.mock_practical_score,
            "term_work_score": self.term_work_score
        }

    @staticmethod
    def from_dict(data):
        student = Student(
            data["name"],
            data["roll_no"],
            data["attendance"],
            data["unit_test_score"],
            data["achievements"],
            data["mock_practical_score"]
        )
        student.term_work_score = data["term_work_score"]
        return student

    def display_details(self):
        print(f"Name: {self.name}")
        print(f"Roll No: {self.roll_no}")
        print(f"Attendance: {self.attendance}%")
        print(f"Unit Test/Prelim Score: {self.unit_test_score}/100")
        print(f"Achievements: {self.achievements}/10")
        print(f"Mock Practical Score: {self.mock_practical_score}/50")
        print(f"Final Term Work Score: {self.term_work_score:.2f}/100")


def display_menu():
    print("\n1. Add Student")
    print("2. Display All Students")
    print("3. Search Student by Roll Number")
    print("4. Edit Student Details")
    print("5. Delete Student")
    print("6. Save Data to File")
    print("7. Load Data from File")
    print("8. Exit")


def add_student(students):
    print("\n--- Add New Student ---")
    try:
        name = input("Enter student's name: ").strip()
        if not name:
            raise ValueError("Name cannot be empty.")
        roll_no = input("Enter roll number: ").strip()
        if not roll_no:
            raise ValueError("Roll number cannot be empty.")
        attendance = float(input("Enter attendance percentage (0-100): "))
        unit_test_score = float(input("Enter Unit Test/Prelim score (0-100): "))
        achievements = float(input("Enter achievements score (0-10): "))
        mock_practical_score = float(input("Enter Mock Practical score (0-50): "))

        student = Student(name, roll_no, attendance, unit_test_score, achievements, mock_practical_score)
        student.calculate_term_work_score()
        students.append(student)
        print("Student added successfully!")
    except ValueError as e:
        print(f"Error: {e}. Please enter valid inputs.")


def display_all_students(students):
    print("\n--- Student Details ---")
    if not students:
        print("No students found.")
    else:
        for student in students:
            student.display_details()
            print("-" * 30)


def search_student(students, roll_no):
    for student in students:
        if student.roll_no == roll_no:
            return student
    return None


def edit_student(students):
    roll_no = input("Enter the roll number of the student to edit: ").strip()
    student = search_student(students, roll_no)
    if student:
        print("Editing details for:", student.name)
        try:
            student.name = input(f"Enter new name (current: {student.name}): ").strip() or student.name
            student.attendance = float(input(f"Enter new attendance (current: {student.attendance}%): ") or student.attendance)
            student.unit_test_score = float(input(f"Enter new Unit Test score (current: {student.unit_test_score}/100): ") or student.unit_test_score)
            student.achievements = float(input(f"Enter new achievements score (current: {student.achievements}/10): ") or student.achievements)
            student.mock_practical_score = float(input(f"Enter new Mock Practical score (current: {student.mock_practical_score}/50): ") or student.mock_practical_score)
            student.calculate_term_work_score()
            print("Student details updated successfully!")
        except ValueError as e:
            print(f"Error: {e}. Please enter valid inputs.")
    else:
        print("Student not found.")


def delete_student(students):
    roll_no = input("Enter the roll number of the student to delete: ").strip()
    student = search_student(students, roll_no)
    if student:
        students.remove(student)
        print("Student deleted successfully!")
    else:
        print("Student not found.")


def save_data_to_file(students, filename="students.json"):
    try:
        with open(filename, "w") as file:
            json.dump([student.to_dict() for student in students], file)
        print("Data saved successfully!")
    except Exception as e:
        print(f"Error saving data: {e}")


def load_data_from_file(students, filename="students.json"):
    try:
        with open(filename, "r") as file:
            data = json.load(file)
            students.clear()
            students.extend(Student.from_dict(student_data) for student_data in data)
        print("Data loaded successfully!")
    except FileNotFoundError:
        print("No saved data found.")
    except Exception as e:
        print(f"Error loading data: {e}")


def main():
    print("\n--- Automated Term Work Assessment ---")
    print("College: Wadia College of Engineering")

    students = []
    display_menu()
    
    while True:
       
        choice = input("Enter your choice: ")

        if choice == "1":
            add_student(students)
        elif choice == "2":
            display_all_students(students)
        elif choice == "3":
            roll_no = input("Enter roll number to search: ").strip()
            student = search_student(students, roll_no)
            if student:
                student.display_details()
            else:
                print("Student not found.")
        elif choice == "4":
            edit_student(students)
        elif choice == "5":
            delete_student(students)
        elif choice == "6":
            save_data_to_file(students)
        elif choice == "7":
            load_data_from_file(students)
        elif choice == "8":
            print("Exiting the program. Goodbye!")
            break
        else:
            print("Invalid choice. Please try again.")


if __name__ == "__main__":
    main()
