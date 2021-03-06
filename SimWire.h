#pragma once
#include <vector>

// need to start using smart pointers more
#include <memory>

namespace hwsim {

// forward declaration of enum WireEnd
enum class WireEnd;

// forward declaration for the graph interfaces
struct SimWireEdge;
struct SimWireVertex;

// class for the simulation representation of a wire, 
// which is used for heat and wave propagation
// do not inherit!
class SimWire
{

	friend class SimNode;
	friend class SimController;

public:

	// struct containing configuration options used in wire initialization
	struct Config 
	{
		unsigned int storeTimesteps;
		unsigned int nx;
		float dx;

		Config(): storeTimesteps(0), nx(0), dx(0) {};

		Config(unsigned int _storeTimesteps, unsigned int _nx, float _dx) :
			storeTimesteps(_storeTimesteps), nx(_nx), dx(_dx)
		{};
	};

	// interface for building a state vector given a size
	class StateInitializer 
	{

	public:
		// this doesn't allocate a vector, it just fills it in
		// (use the length!)
		virtual void operator()(std::vector<float>& vec) const = 0;
	};

	// struct containing pointers to state initializers
	struct InitState 
	{
		std::shared_ptr<StateInitializer> initWave;
		std::shared_ptr<StateInitializer> initWaveVelocity;
		std::shared_ptr<StateInitializer> initHeat;

		// these will probably be taken out later and put somewhere else,
		// because they're arguably not part of the 'state'
		std::shared_ptr<StateInitializer> waveSpeed;
		std::shared_ptr<StateInitializer> damping;
		std::shared_ptr<StateInitializer> diffusivity;

		// return true if all out pointers are valid
		bool isValid() const {
			return initWave && initWaveVelocity && initHeat && 
				waveSpeed && damping && diffusivity;
		};
	};

	SimWire(SimWireEdge* _edge, SimController& simCtrl_);
	SimWire(SimWireEdge* _edge, SimController& simCtrl_, 
			const Config& config);

	~SimWire();

	// updates one timestep for both wave and heat
	void update(float dt);
	
	// reset the wire to it's initial state
	void reset(float dt);
	
	// resetting just uses this internally 
	void initializeInPlace(const InitState& initState, float dt);

	// initialize the wire, reallocating the heat/wave buffers as necessary
	bool initialize(const Config& config, const InitState& initState, float dt);

	// return references to the wave and heat data at the 'current' time
	const std::vector<float>& getWave() const;
	const std::vector<float>& getHeat() const;

	// generalized versions of the above functions:
	// return the wave or heat n timesteps ago
	const std::vector<float>& getWavePast(unsigned int n) const;
	const std::vector<float>& getHeatPast(unsigned int n) const;

	// get the wave/heat in 'the future' - used by SimNode to obtain the 
	// future calculated values before the temporal index has been updated
	const std::vector<float>& getWaveFuture() const;
	const std::vector<float>& getHeatFuture() const;

	// set/get how many timesteps we're storing
	// error if setting to values smaller than 3
	void setStoreTimesteps(unsigned int storeTimesteps);
	unsigned int getStoreTimesteps() const;

	// get/set config
	bool setConfig(const Config& config);
	const Config& getConfig() const;
	
	// get/set InitState
	bool setInitState(const InitState& initState);
	const InitState& getInitState() const;

	// has this wire been initialized?
	bool isInitialized() const;

	// is the config valid?
	bool isConfigValid() const;
	
	// TODO: should this be a reference?
	// the corresponding SimWireEdge graph interface
	SimWireEdge* edge;
	
	// the SimController object for this wire
	SimController& simCtrl;

private:

	// compute wave spatial and temporal derivatives
	void computeWaveDerivatives(float dt);

	// compuate heat spatial and temporal derivatives
	void computeHeatDerivatives(float dt);

	// update the boundaries, using the nodes
	void updateWaveBoundaries(std::vector<float>&wave_next, float dt);
	void updateHeatBoundaries(std::vector<float>&heat_next, float dt);

	// update the temporal index - done at the start/very end of each sim tick
	void updateTemporalIndex();

	// get the next temporal index
	unsigned int getNextTemporalIndex();

	// resize the vectors that store the state
	void allocateState();
	void initializeState(const InitState& initState, float dt);
	
	// store the configuration provided to us
	Config config;
	
	// store the InitState provided to us (copy)
	// remember copying is cheap here (best case) because InitState is
	// composed of state builders, not actual vectors
	InitState initState;

	// the wave speed over the wire
	std::vector<float> waveSpeed;

	// the damping over the wire
	std::vector<float> damping;

	// the "thermal" diffusivity of the wire
	std::vector<float> diffusivity;

	// contains the wave amplitude data, for the past n (probably 3) timesteps
	std::vector<std::vector<float>> wave;

	// contains the heat data, for the past n (probably 3 (?)) timesteps
	std::vector<std::vector<float>> heat;

	// storage for derivatives of various orders
	std::vector<std::vector<float>> wave_x;
	std::vector<std::vector<float>> wave_xx;
	std::vector<std::vector<float>> wave_t;

	std::vector<std::vector<float>> heat_x;
	std::vector<std::vector<float>> heat_xx;
	
	// store the 'damping energy differential' - energy lost due to damping
	
	// what's the index of the 'current' timestep?
	unsigned int _currentTimestepIndex;

	// has this wire been initialized?
	bool _isInitialized;

	// is the current wire configuration valid?
	bool _isConfigValid;
};

};
