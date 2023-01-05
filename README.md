GYM APP made in C++

It has the following functionalities:
-tracks your personal records (PRs) for each lift: squat, bench and deadlift
-logs for you to record your workouts and track your progress
-offers tips and exercises to help you improve your form and lift more weight
-calculates your one-rep max (1RM) based on the weights and reps you've lifted
-provide a personalized workout plan to help you reach your goals(still needs some work)
-has a command-line interface 

TO BE ADDED IN THE FUTURE:
    Add a feature that allows the user to view the personal records for a specific lift, along with the form tips and assistance exercises for that lift. This could be done by adding a new command to the command-line interface and implementing a new member function in the RecordsTracker class.

    Add a feature that allows the user to filter the workout log by lift name, date, or weight lifted. This could be done by adding a new command to the command-line interface and implementing a new member function in the RecordsTracker class.

    Add a feature that allows the user to view their progress over time by plotting their personal records on a graph. This could be done by using a library like matplotlib to generate the graph.

    Add a feature that allows the user to set goals for each lift and track their progress towards those goals. This could be done by adding a new field to the Lift struct to store the goal weight and implementing a new member function in the RecordsTracker class that returns the percentage of the goal that has been achieved.

    Add a feature that suggests new personal records for the user based on their previous performances. This could be done by analyzing the user's workout log and using a formula to estimate their potential one-rep max for each lift.
