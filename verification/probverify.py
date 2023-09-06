using JuMP
using Distributions
import CPLEX
import StatsBase
import MathOptInterface as MOI

lbox = 20
rangebox = 20
ntestrun = 1 # 10000
nsample = 100
cis = [1,2,3]

function pow(x, e)
   return x^e
end


function eval(box, refexponents, xstar)
   dw0 = box[2] - box[1]
   dw1 = box[4] - box[3]
   dw2 = box[6] - box[5]

   #/* compute function values of \f$ f_0, f_1, f_2 \f$ at vetices */
   f0w0l = pow(box[1], refexponents[1])
   f0w0u = pow(box[2], refexponents[1])
   f1w1l = pow(box[3], refexponents[2])
   f1w1u = pow(box[4], refexponents[2])
   f2w2l = pow(box[5], refexponents[3])
   f2w2u = pow(box[6], refexponents[3])
   facetcoefs = [[0.0, 0.0, 0.0],[0.0,0.0,0.0]]
   facetconstant = [0.0,0.0]

   #/* underestimator 1: \f$ fw0uw1uw2u + (fw0uw1uw2u - fw0lw1uw2u) / (dw0) * (x0 - w0u) + (fw0uw1uw2u - fw0uw1lw2u) / (dw1) * (x1 - w1u) + (fw0uw1uw2u - fw0uw1uw2l) / (dw2) * (x2 - w2u) \f$ */
   fw0uw1uw2u = f0w0u * f1w1u * f2w2u
   fw0lw1uw2u = f0w0l * f1w1u * f2w2u
   fw0uw1lw2u = f0w0u * f1w1l * f2w2u
   fw0uw1uw2l = f0w0u * f1w1u * f2w2l
   facetcoefs[1][1] = (fw0uw1uw2u - fw0lw1uw2u) / dw0
   facetcoefs[1][2] = (fw0uw1uw2u - fw0uw1lw2u) / dw1
   facetcoefs[1][3] = (fw0uw1uw2u - fw0uw1uw2l) / dw2
   facetconstant[1] = fw0uw1uw2u  - facetcoefs[1][1] * box[2] - facetcoefs[1][2] * box[4] - facetcoefs[1][3] * box[6]
   fcase0 = facetconstant[1] + facetcoefs[1][1] * xstar[1] + facetcoefs[1][2] * xstar[2] + facetcoefs[1][3] * xstar[3]

   #/* underestimator 2: \f$ fw0lw1lw2l + (fw0uw1lw2l - fw0lw1lw2l) / (dw0) * (x0 - w0l) + (fw0lw1uw2l - fw0lw1lw2l) / (dw1) * (x1 - w1l) + (fw0lw1lw2u - fw0lw1lw2l) / (dw2) * (x2 - w2l) \f$ */
   fw0lw1lw2l = f0w0l * f1w1l * f2w2l
   fw0uw1lw2l = f0w0u * f1w1l * f2w2l
   fw0lw1uw2l = f0w0l * f1w1u * f2w2l
   fw0lw1lw2u = f0w0l * f1w1l * f2w2u
   facetcoefs[2][1] = (fw0uw1lw2l - fw0lw1lw2l) / dw0
   facetcoefs[2][2] = (fw0lw1uw2l - fw0lw1lw2l) / dw1
   facetcoefs[2][3] = (fw0lw1lw2u - fw0lw1lw2l) / dw2
   facetconstant[2] = fw0lw1lw2l - facetcoefs[2][1] * box[1] - facetcoefs[2][2] * box[3] - facetcoefs[2][3] * box[5]
   fcase1 = facetconstant[2] + facetcoefs[2][1] * xstar[1] + facetcoefs[2][2] * xstar[2] + facetcoefs[2][3] * xstar[3]

   return max(fcase0, fcase1)
end

function mapbox(i,j)
   return  ((i - 1) >> (j - 1)) & 1 > 0 ? 2*j : 2*j - 1
end


function evalLP(box, refexponents, xstar)
   varids = collect(1:8)
   dims = collect(1:3)
   model = Model(CPLEX.Optimizer)
   set_silent(model)
   @variables(model, begin
      0 <= x[i in varids] <= 1
   end)

   f = [1.0 for i in varids]
   for i in varids
      for j in dims
         f[i] *= pow(box[ mapbox(i,j)], refexponents[j])
      end
   end

   @constraints(model, begin
      1 == sum(x[i] for i in varids)
      [j in dims], xstar[j] == sum(box[mapbox(i,j)] * x[i] for i in varids)
   end)


   @objective(model, Max,  sum(f[i]*x[i] for i in varids) )


   optimize!(model)
   return objective_value(model)
end

for i in collect(1:ntestrun)
   boxes = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
   for i in cis
      boxes[2*i - 1] = rand(Uniform(1e-1, lbox))
      boxes[2*i] = boxes[2*i - 1] + rand(Uniform(1, rangebox))
   end
   exponents = [0.0, 0.0, 0.0]
   sumexp = 0.0
   for i in cis
      exponents[i] = rand(Uniform(1e-1, 1))
      sumexp += exponents[i] 
   end
   sumexp *=  rand(Uniform(1, 3))
   for i in cis
      exponents[i] /= sumexp
   end
   for s in collect(1:nsample)
      vals =  [0.0, 0.0, 0.0]
      for i in cis
         c = rand(Uniform(1e-2, 1 - 1e-2))
         vals[i] = boxes[2*i - 1] * c  + boxes[2*i] * (1-c)
      end
      feval = eval(boxes, exponents, vals)
      fevalLP = evalLP(boxes, exponents, vals)
      if abs(feval - fevalLP) < 1e-4
         continue   
      else
         print(s, " ", feval, " ", fevalLP)
         @assert(false)
      end
   end
end