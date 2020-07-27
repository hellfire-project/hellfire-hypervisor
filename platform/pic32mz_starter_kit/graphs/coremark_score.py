import matplotlib.pyplot as plt
import numpy as np
 
# Create bars
barWidth = 0.95
barsn = [589.93]
bars1 = [588.32]
bars2 = [587.36, 293.63, 293.72]
bars3 = [585.91, 195.25, 195.22, 195.44]
bars4 = [585.39, 146.2, 146.3, 146.34,  146.55]
all_bars = barsn + bars1 + bars2 + bars3 + bars4

 
# The X position of bars
rn = [1]
r1 = [2]
r2 = [3, 4, 5]
r3 = [6, 7, 8, 9]
r4 = [10, 11, 12, 13, 14]
all_r = rn + r1 + r2 + r3 + r4

 
# Create barplot
plt.bar(rn, barsn, width = barWidth, color = (0.3,0.1,0.4,0.6), label='Native')
plt.bar(r1, bars1, width = barWidth, color = (0.3,0.5,0.4,0.6), label='One VM')
plt.bar(r2, bars2, width = barWidth, color = (0.3,0.9,0.8,0.6), label='Two VMs')
plt.bar(r3, bars3, width = barWidth, color = (0.6,0.9,0.4,0.6), label='Three VMs')
plt.bar(r4, bars4, width = barWidth, color = (0.3,0.9,0.4,0.6), label='Four VMs')

# Create legend
plt.legend()
 
# Text below each barplot with a rotation at 90°
#plt.xticks([barWidth+0.1, 
 #           1+barWidth, 
#            3+barWidth, 
#            6+barWidth, 
#            8+barWidth],
#            ['Native', 'One', 'Two', 'Three', 'Four'])
plt.xticks([],[])
plt.xlabel('System Configuration', fontweight='bold')

 
# Create labels
label = [   '589.93', 
            '588.32', 
            '587.36', '293.63', '293.72',   
            '585.91', '195.25',    '195.22',  '195.44',
            '585.39', '146.20', '146.30', '146.34', '146.55']

# Text on the top of each barplot
for i in range(len(all_bars)):
    plt.text(x = all_r[i]-0.4, y = all_bars[i]+0.4, s = label[i], size = 5)
 
# Adjust the margins
plt.subplots_adjust(bottom= 0.2, top = 0.98)
 
# Show graphic
#plt.show()

plt.savefig('coremark_score.eps', format='eps')


