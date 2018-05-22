This file describes how lambda expressions are expanded to callable class templates

Example:
```c++
int main(){
  auto check = [](){return true};
  if(check())
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
```

Produces 1 synthetic function:
  constexpr bool main$lambda1(void)noexcept{
    return true;
  }
In addition, the check variable gets the new type:
  
  ```c++
  lambda_Texpression<lambda_Tconstexpr,void,lambda_Tnoexcept,bool,void>
  ```
  
  And check is initialized with `lambda_Texpression<lambda_Tconstexpr,void,lambda_Tnoexcept,bool,void>(main$lambda1);`
  
The type defines the following methods:
```c++
operator bool(*)noexcept()()noexcept -> which returns the address of the function.
and (because its constexpr and noexcept)
constexpr bool operator()()noexcept;
```
 
Example with captures
```c++
  int main(){
    int val = 0;
    int out = 0;
    auto accumulate = [val,&out](int x,int y)noexcept{ 
      int tmp = out + y;
      out = val + x;
      return tmp;
    };
    pair<int,int> vals[] = {{0,1},{2,3},{4,5},{6,7}};
    for(auto [x,y]:vals)
      val += accumulate(x,y);

    cout << val << ", "<<out<<endl;
    return EXIT_SUCCESS;

  }
```
Which Generates the interesting method:
```c++
  int main$lambda2(tuple<const int,reference_wrapper<int>> lambda2$captures,int x,int y)noexcept{
    int tmp =  get<1>(lambda2$captures) + y;
    get<1>(lambda2$captures) = x + get<0>(lambda2$captures);
    return tmp;
  }
```
And the potentially even more interesting instantiation of the lambda_Texpression template
```c++
  lambda_Texpression<void,void,lambda_Tnoexcept,int,tuple<const int,reference_wrapper<int>,int,int>
 Which only defines a single method (which is noexcept):
  int operator()(int,int)noexcept;
```

The construction of the expression, is even more interesting. From here on, the type for the expression is denoted by lambda_t
```c++
  lambda_t(std::forward_as_tuple<const int,reference_wrapper<int>>(val,ref(out)),main$lambda2);
  
  If mutable was used, then the function will look more like this:
  
  int main$lambda2(tuple<const int,reference_wrapper<int>> lambda2$captures,int x,int y)noexcept{
    int lambda2$mutable_capture$val = get<0>(lambda2$captures);
    int tmp = get<1>(lambda2$captures) + y;
    get<1>(lambda2$captures) = x + lambda2$mutable_capture$val;
    return tmp;
  }
```
  notice that despite the fact that mutable was used, it doesn't remove the const qualifier from val,
  instead it generates a new dummy variable which has a very interesting name.
  
  The synthetic names of the lambda functions and the mutable lambda captures are given by:
  
  ```
  <name of defining function>$lambda<lambda number> for the lambda expression's underlying function
  and <lambda name>$<variable name> for mutable captured variables.
  ```
  
  The tuples are used for captures for no real reason.
  
  Finally, templates and "auto" parameters define a family of functions.
  
  Specifically, the following lambda definition
  ```c++
    auto lambda = [](auto val){return val+val};
  ```
  This does not define a synthetic lambda function, but instead inlines the expression directly into the lambda
  
  And the following lambda types:
  ```c++
  template<typename T> main$lambda3$template_parameters
  lambda_Texpression<void,main$lambda3$template_parameters,void,lambda_Tplaceholder_decltype_auto,lambda_Tplaceholder_template_0>
  ```
  
  Which has the following lone method
  
  ```c++
  template<typename T> decltype(auto) operator()(T val)
  ```
  
  
