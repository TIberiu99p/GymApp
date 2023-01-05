#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// A Lift represents a type of weightlifting exercise, such as "bench press" or "deadlift".
struct Lift {
  std::string name;
  int personal_record;
  std::vector<std::string> form_tips;
  std::vector<std::string> assistance_exercises;
};

// A Workout represents a single weightlifting session. It contains the date of the workout,
// the name of the lift, and the weight and reps lifted.
struct Workout {
  std::string date;
  std::string lift_name;
  int weight;
  int reps;
};

// A WorkoutPlan represents a personalized workout plan for a user. It contains a list of lifts
// that the user should focus on, along with the number of sets and reps the user should do for
// each lift.
struct WorkoutPlan {
  std::vector<std::string> lifts;
  std::vector<int> sets;
  std::vector<int> reps;
};

// The RecordsTracker keeps track of the personal records for multiple lifts and stores a log of
// all workouts. It also offers form tips and assistance exercises for each lift, and it provides
// a personalized workout plan to help users reach their goals.
class RecordsTracker {
 public:
  void SetLiftRecord(const std::string& lift_name, int new_record) {
    // Check if the lift already exists in the records tracker.
    auto it = records_.find(lift_name);
    if (it == records_.end()) {
      // If the lift doesn't exist, add it to the records tracker with the new record.
      Lift lift;
      lift.name = lift_name;
      lift.personal_record = new_record;
      records_.emplace(lift_name, lift);
    } else {
      // If the lift already exists, update its record if the new record is higher.
      Lift& lift = it->second;
      if (new_record > lift.personal_record) {
        lift.personal_record = new_record;
      }
    }
  }

  int GetLiftRecord(const std::string& lift_name) const {
    // Check if the lift exists in the records tracker.
    auto it = records_.find(lift_name);
    if (it == records_.end()) {
      // If the lift doesn't exist, return -1.
      return -1;
    }

    // Return the lift's personal record.
    return it->second.personal_record;
  }

    void AddFormTip(const std::string& lift_name, const std::string& form_tip) {
    // Check if the lift exists in the records tracker.
    auto it = records_.find(lift_name);
    if (it != records_.end()) {
      // If the lift exists, add the form tip to the lift's form tips vector.
      Lift& lift = it->second;
      lift.form_tips.push_back(form_tip);
    }
  }

  void AddAssistanceExercise(const std::string& lift_name, const std::string& exercise) {
    // Check if the lift exists in the records tracker.
    auto it = records_.find(lift_name);
    if (it != records_.end()) {
      // If the lift exists, add the assistance exercise to the lift's assistance exercises vector.
      Lift& lift = it->second;
      lift.assistance_exercises.push_back(exercise);
    }
  }

  void AddWorkout(const Workout& workout) {
    log_.push_back(workout);
  }

  void PrintWorkoutLog() const {
    std::cout << "Workout Log:\n";
    for (const Workout& workout : log_) {
      std::cout << workout.date << ": " << workout.lift_name << " - " << workout.weight << " lbs x " << workout.reps << "\n";
    }
  }

  int CalculateOneRepMax(const std::string& lift_name, int weight, int reps) const {
    // Check if the lift exists in the records tracker.
    auto it = records_.find(lift_name);
    if (it == records_.end()) {
      // If the lift doesn't exist, return -1.
      return -1;
    }

    // Use the Epley formula to calculate the 1RM.
    return static_cast<int>(weight * (1 + reps / 30.0));
  }

  void PrintLiftInfo(const std::string& lift_name) const {
    // Check if the lift exists in the records tracker.
    auto it = records_.find(lift_name);
    if (it == records_.end()) {
      std::cout << "Lift not found.\n";
      return;
    }

    // Print the lift's personal record and form tips.
    const Lift& lift = it->second;
    std::cout << "Personal Record: " << lift.personal_record << " lbs\n";
    std::cout << "Form Tips:\n";
    for (const std::string& tip : lift.form_tips) {
      std::cout << "- " << tip << "\n";
    }

    // Print the lift's assistance exercises.
    std::cout << "Assistance Exercises:\n";
    for (const std::string& exercise : lift.assistance_exercises) {
      std::cout << "- " << exercise << "\n";
    }
  }

    void PrintRecords() const {
    std::cout << "Personal Records:\n";
    for (const auto& record : records_) {
      const Lift& lift = record.second;
      std::cout << lift.name << ": " << lift.personal_record << " lbs\n";
    }
  }

  WorkoutPlan GetWorkoutPlan(int goal_weight) const {
    WorkoutPlan plan;
    for (const auto& record : records_) {
      const Lift& lift = record.second;
      if (lift.personal_record < goal_weight) {
        plan.lifts.push_back(lift.name);
        plan.sets.push_back(3);
        plan.reps.push_back(8);
      }
    }
    return plan;
  }

 private:
  // records_ is a map that maps lift names to Lift objects.
  std::unordered_map<std::string, Lift> records_;

  // log_ is a vector that stores all of the workouts in the workout log.
  std::vector<Workout> log_;
};

int main() {
  RecordsTracker tracker;

  std::string command;
  std::cout << "Enter command (set, get, tip, assist, workout, log, records, 1rm, plan, exit): ";
  std::cin >> command;

  while (command != "exit") {
    if (command == "set") {
      std::string lift_name;
      int new_record;
      std::cin >> lift_name >> new_record;
      tracker.SetLiftRecord(lift_name, new_record);
    } else if (command == "get") {
      std::string lift_name;
      std::cin >> lift_name;
      int record = tracker.GetLiftRecord(lift_name);
      if (record == -1) {
              std::cout << "Lift not found.\n";
      } else {
        std::cout << "Personal Record: " << record << " lbs\n";
      }
    } else if (command == "tip") {
      std::string lift_name;
      std::string form_tip;
      std::cin >> lift_name >> form_tip;
      tracker.AddFormTip(lift_name, form_tip);
    } else if (command == "assist") {
      std::string lift_name;
      std::string exercise;
      std::cin >> lift_name >> exercise;
      tracker.AddAssistanceExercise(lift_name, exercise);
    } else if (command == "workout") {
      Workout workout;
      std::cin >> workout.date >> workout.lift_name >> workout.weight >> workout.reps;
      tracker.AddWorkout(workout);
    } else if (command == "log") {
      tracker.PrintWorkoutLog();
    } else if (command == "records") {
      tracker.PrintRecords();
    } else if (command == "1rm") {
      std::string lift_name;
      int weight, reps;
      std::cin >> lift_name >> weight >> reps;
      int one_rep_max = tracker.CalculateOneRepMax(lift_name, weight, reps);
      if (one_rep_max == -1) {
        std::cout << "Lift not found.\n";
      } else {
        std::cout << "One-Rep Max: " << one_rep_max << " lbs\n";
      }
    } else if (command == "plan") {
      int goal_weight;
      std::cin >> goal_weight;
      WorkoutPlan plan = tracker.GetWorkoutPlan(goal_weight);
      std::cout << "Workout Plan:\n";
      for (int i = 0; i < plan.lifts.size(); ++i) {
        std::cout << plan.lifts[i] << ": " << plan.sets[i] << " sets of " << plan.reps[i] << "\n";
      }
    } else {
      std::cout << "Invalid command.\n";
    }

    std::cout << "\nEnter command (set, get, tip, assist, workout, log, records, 1rm, plan, exit): ";
    std::cin >> command;
  }

  return 0;
}
