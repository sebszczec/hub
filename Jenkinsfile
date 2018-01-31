pipeline {
    agent any 

    stages {
        stage('Build docker image') { 
            steps { 
                sh 'make -f makefile.docker build_docker_image' 
            }
        }
	stage('Build HUB'){
	    steps {
	        sh 'make -f makefile.docker build_hub'
	    }
	}
        stage('Run UT'){
            steps {
                sh 'make -f makefile.docker run_ut' 
		junit "test_detail.xml"
            }
        }
        stage('Run FT'){
            steps {
                sh 'make -f makefile.docker run_ft'
            }
        }
    }
}
