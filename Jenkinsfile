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
        stage('Generate statistics'){
            steps {
                sh 'make -f makefile.docker generate_cobertura'
                sh 'make -f makefile.docker generate_cloc'
            }
        }
    }
    post {
        always {
	    step([$class: 'CoberturaPublisher', autoUpdateHealth: false, autoUpdateStability: false, coberturaReportFile: 'ut_cobertura.xml', failUnhealthy: false, failUnstable: false, maxNumberOfBuilds: 0, onlyStable: false, sourceEncoding: 'ASCII', zoomCoverageChart: false])
	    sloccountPublish encoding: '', pattern: ''
	    archiveArtifacts artifacts: '*.xml', fingerprint: true
	}
    }
}
