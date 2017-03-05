function J = computeCost(X, y, theta)
%COMPUTECOST Compute cost for linear regression
%   J = COMPUTECOST(X, y, theta) computes the cost of using theta as the
%   parameter for linear regression to fit the data points in X and y

% Initialize some useful values
m = length(y); % number of training examples

% You need to return the following variables correctly 
J = 0;

% ====================== YOUR CODE HERE ======================
% Instructions: Compute the cost of a particular choice of theta
%               You should set J to the cost.

hypothesis = X * theta;
sm = ( hypothesis - y ) .^ 2;
J = sm / ( 2 * m );


% Alternate code

%for i = 1 : m
%  sm = (hypothesis(i) - y(i)) ^ 2;
%  J = J + (sm / (2 * m) );

% =========================================================================

end
