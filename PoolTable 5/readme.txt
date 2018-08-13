/******************************************************************************
 * Author: Wangbei Shen
 * 
 * This is a Pool simulation game written for my course info3220.
 * It is built upon a collision detection,composite ball split，ball arm ,ball pocket, return state using 'r',volume 
 * silder control and score count animation program 
 * designed by Wangbei Shen. 
 * 
 * Design pattern using: Abstract factory,builder,composite,adaptor,memento
 * 
 * 
 * ****************************************************************************


Wangbei Shen's Pool  Game:

===========================================================================================
-------------------------------------------------------------------------------------------
GOAL:
-------------------------------------------------------------------------------------------
- The goal of the game is simple; Player can use cue to hit ball to pocket.
  Composite ball can break to subball due to strength smaller than energy of collision(assignment2)
- User can control volume of background music from 0-100 through move the slider bar.(small entension)
- User can determine who win the game through the socre in the user interface. It count the hit number,if
  the number is small,it means it use less count to hit the balls into the pocket.Obviously,the value of 
  different colour ball is equivalent.(small extension)
- User can pree 'r' to return to the last step when the all balls in the table is stop.
  Otherwise, pressing r will cause game back to intial.
- User can add ball that they set, like size, speed, strength, color when runnning the game.
  (I think it is a big extension )

-------------------------------------------------------------------------------------------

Precautions：
-------------------------------------------------------------------------------------------
- User need to press focus button after they add ball, otherwise you will keep type r in the 
  user interface.After you go back previous step, you should unlock the focus.
