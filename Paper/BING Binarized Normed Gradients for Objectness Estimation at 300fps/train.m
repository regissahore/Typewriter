disp('Generating Training Data');
generate_train_set();
disp('Train Filter Score Linear Model');
train_filter_model();
disp('Get Binary Approximation Model');
binary_approximation_model();
disp('Finished');