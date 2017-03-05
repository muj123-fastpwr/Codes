function [theta, J_history] = gradientDescentMulti(X, y, theta, alpha, num_iters)
%GRADIENTDESCENTMULTI Performs gradient descent to learn theta
%   theta = GRADIENTDESCENTMULTI(x, y, theta, alpha, num_iters) updates theta by
%   taking num_iters gradient steps with learning rate alpha

% Initialize some useful values
m = length(y); % number of training examples
J_history = zeros(num_iters, 1);

for iter = 1:num_iters

    % ====================== YOUR CODE HERE ======================
    % Instructions: Perform a single gradient step on the parameter vector
    %               theta. 
    %
    % Hint: While debugging, it can be useful to print out the values
    %       of the cost function (computeCostMulti) and gradient here.
    
    
    % order of X = m x 3
    % order of y = m x 1
    % order of theta = 3 x 1 
    % order of h = m x 1
    % size( X , 2 ) = 3
    % repmat( ( h - y ), 1, size( X , 2 ) ) = [ (h-y) (h-y) (h-y) ]
    
    h = X * theta;
    rep = repmat( ( h - y ), 1, size( X , 2 ) );
    delta = ( 1 / m ) * sum( X .* rep );
    
    theta = (theta' - (alpha * delta))';



    % ============================================================

    % Save the cost J in every iteration    
    J_history(iter) = computeCostMulti(X, y, theta);

end

end
