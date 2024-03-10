#! /usr/bin/env python

import rospy
from assignment_2_2023.srv import LastTarget,LastTargetRequest
from sensor_msgs.msg import LaserScan


def clbk_laser(msg):
    global regions
    regions = {
        'right':  min(min(msg.ranges[0:143]), 10),
        'fright': min(min(msg.ranges[144:287]), 10),
        'front':  min(min(msg.ranges[288:431]), 10),
        'fleft':  min(min(msg.ranges[432:575]), 10),
        'left':   min(min(msg.ranges[576:713]), 10),
    }
    min_key = min(regions, key=regions.get)
    min_value = regions[min_key]

    print(f"L'elemento con il valore minimo è: {min_key} con valore {min_value}")
    

def main():

	# init a node as usual
	rospy.init_node('lastTargetClient')

	# wait for this service to be running
	# Ideally, this service should run 24/7, but remember it's fake :) 
	rospy.wait_for_service('/lastTarget')
	sub = rospy.Subscriber('/scan', LaserScan, clbk_laser)
	# Create the connection to the service. Remeber it's a Trigger service
	sos_service = rospy.ServiceProxy('/lastTarget', LastTarget)

	# Create an object of type TriggerRequest. We need a TriggerRequest for a Trigger service
	# We don't need to pass any argument because it doesn't take any
	sos = LastTargetRequest()

	# Now send the request through the connection
	'''result = sos_service(sos)
	min_key = min(regions, key=regions.get)
	min_value = regions[min_key]

	print(f"L'elemento con il valore minimo è: {min_key} con valore {min_value}")'''
	rospy.spin()
	


# Done, let's see the result!
	print(result)
	

	
if __name__ == '__main__':
    main()
