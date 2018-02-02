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
	stage('Generate cobertura'){
	    steps {
	    	sh 'make -f makefile.docker generate_cobertura'
	    }
	|
        stage('Run UT (+Valgrind)'){
            steps {
                sh 'make -f makefile.docker run_vut' 
		junit "test_detail.xml"
            }
        }
        stage('Run FT'){
            steps {
                sh 'make -f makefile.docker run_ft'
		junit "functional_tests.xml"
            }
        }
    }
}
